#!/bin/bash

# Action:
# 对 ./test 所有的测试用例进行自动化测试,
# 执行 ring run xxx.ring 命令 运行, 得到输出结果 xxx.ring.result.tmp, 
# 与预期结果 xxx.ring.result 进行比对
# 会输出 测试的详情和测试数量汇总

# Usage:
# 1. 触发全部自动化测试
#    make testall
#    或者 bash ./test/automated-testing.sh
# 2. 测试的轮数
#    默认1轮, 可调整 TEST_LOOP_NUM
# 3. 控制测试的模块: 
#    调整 TEST_MODELS 
# 4. 控制不测试的case: 
#    调整 NOT_TEST_FILES 
# 5. 是否输出测试用例表: 
#    调整 IS_EXPORT_TEST_DETAIL_SUMMARY
#    测试描述会从测试文件中导出, 匹配前缀 // TestDetail:
#    测试用例中导出测试失败的原因，匹配前缀 // Fatal:

# 测试的轮数, 用于多次执行
TEST_LOOP_NUM=1

not_test_num=0
succ_num=0
fail_num=0
all_num=0



# 测试的可执行文件
# 可通过第1个参数指定 TEST_RING_BIN
TEST_RING_BIN="./bin/ring"
if [[ "$1" != "" ]]; then
    TEST_RING_BIN="$1"
fi

# ring 命令行 option
TEST_RING_OPTION="-O1"

# 测试功能 ring run xxx.ring
TEST_RING_COMMAND="run"


TEST_COMMAND="${TEST_RING_BIN} ${TEST_RING_OPTION} ${TEST_RING_COMMAND}"

# 要测试的文件夹
TEST_PATH="./test"
TEST_MODELS=(
    "001-bool"
    "002-int"
    "002-int64"
    "003-double"
    "004-string"

    "001-basic-type" 

    "002-operator" 
    "002-operator/minus" 

    "003-native-function" 
    "004-derive-function" 
    "004-derive-function/pass-argument" 
    "004-derive-function/return-value" 

    "006-variable" 
    "007-array"
    "008-class" 
    "010-main-entry" 
    "011-global-variable" 
    "012-local-variable"
    "013-gc"

    "020-array-bool"
    "021-array-int"
    "021-array-int64"
    "022-array-double"
    "023-array-string"
    "024-array-class"

    "030-if"
    "031-for"
    "032-do-for"
    "033-for-range"

    "060-std-package-debug"
    "061-std-package-fmt"
    "062-std-package-reflect"
    "063-std-package-os"
    "064-std-package-vm"
    "065-std-package-io"
    "066-std-package-time"
    )

# 跳过测试的case
NOT_TEST_FILES=(

  "./test/013-gc/gc-000.ring" 
  # 数组的地址  如何进行 自动化测试


  "./test/002-operator/arith-oper-002.ring"
  # double 数值比对, 存在bug

#   "./test/062-std-package-reflect/reflect-001.ring"
  # 1. class-object数组，typeof获取不到正确的类型
  # 2. 针对多维数组，typeof获取不到正确的类型
  # 2023-01-31

  "./test/002-operator/arith-oper-003.ring"
  # 还没有支持括号运算符



  "./test/060-std-package-debug/debug-000.ring"
  # 只用来测试 ring rdb


  "./test/002-int64/default-value-003.ring"
  # 暂时还没啥用

  "./test/065-std-package-io/000.ring"

  )

# 测试的结果文件, 主要用于存放本次测试的失败结果
TEST_RESULT="./automated-testing.sh.result"



# 输出ring-测试用例表
# 是否输出测试用例表: 0/1
IS_EXPORT_TEST_DETAIL_SUMMARY=0
# 输出测试用例表文件
TEST_DETAIL_SUMMARY="./test/ring-测试用例表.md.raw"
# 在测试文件中，可以单独写几行用于描述测试的细节
# 用 `// TestDetail:` 开始的行表示
# 用 `// BUG:` 开始的行表示 ring编译器存在BUG，需要及时修复
TEST_DETAIL_PREFIX="^// TestDetail:"

# 如何在测试用例中描述测试的细节
# 用`// TestDetail:` 开始的行表示, 可以多行表示
# 示例: 
# // TestDetail: 测试描述1
# // TestDetail: 测试描述2
# // TestDetail: 测试对象嵌套的初始化
# // TestDetail: 测试嵌套访问method
# // TestDetail: ```
# // TestDetail:     测试用例核心代码
# // TestDetail: ```




# 去除颜色控制字符
STRIP_COLOR="sed -r 's/\x1B\[([0-9]{1,2}(;[0-9]{1,2})?)?[m|K]//g'"




isNotTestFile(){
    for i in ${NOT_TEST_FILES[@]} ; do
      [ "$i" == "$1" ] && return 1
    done
    return 0
}

# 导出一个的测试用例case 说明和 测试情况
exportTestCase(){
    num=$1
    model=$2
    source_code_file=$3
    result=$5

    if [[ $num -eq 1 ]];then
        echo "" > $TEST_DETAIL_SUMMARY
        printf "# Ring 测试用例表\n" >> $TEST_DETAIL_SUMMARY
        printf "\n\n" >> $TEST_DETAIL_SUMMARY
        printf "- 测试时间:" >> $TEST_DETAIL_SUMMARY
        echo $(date +"%Y-%m-%d %H:%M:%S")  >> $TEST_DETAIL_SUMMARY
        printf "\n\n" >> $TEST_DETAIL_SUMMARY
        printf "|Num | 模块 | 文件                           | 测试内容 | 通过 |\n" >> $TEST_DETAIL_SUMMARY
        printf "|--- | -----| ------------------------------| -------- | -- |\n" >> $TEST_DETAIL_SUMMARY
    fi


    tmp=$(grep "^// TestDetail:" $source_code_file | awk -F"// TestDetail: " '{print $2}')
    testDetail=${tmp//$'\n'/<br>}
    printf  "| %-4s | *%-20s | %-80s | %-80s | %-10s |\n" $num $model $source_code_file "$testDetail" $result >> $TEST_DETAIL_SUMMARY

}

autoTestAction(){
    model=$1
    source_code_file=$2"/"$3
    run_result_file=$2"/"$3".result"
    run_result_file_tmp=$2"/"$3".result.tmp"
    result=""


    # 不测试的用例
    isNotTestFile $source_code_file
    if [[ "$?" -eq 1 ]];then
        result="NOTTEST"
        let not_test_num++
        printf "%-4s %-25s %-80s %-80s \033[33m[%s]\033[0m\n" $all_num $model $source_code_file $run_result_file $result
        return
    fi

    let all_num++


    $TEST_COMMAND $source_code_file &> $run_result_file_tmp
    if [[ "$?" -ne 0 ]];then
        result="FAILED"
        let fail_num++
        echo $source_code_file >> $TEST_RESULT
        printf "%-4s %-25s %-80s %-80s \033[31m[%s]\033[0m\n" $all_num $model $source_code_file $run_result_file $result
        return
    fi
    
    diff $run_result_file $run_result_file_tmp

    if [[ "$?" -eq 0 ]];then
        result="PASS"
        let succ_num++
        printf "%-4s %-25s %-80s %-80s \033[32m[%s]\033[0m\n" $all_num $model $source_code_file $run_result_file $result
    else
        result="FAILED"
        let fail_num++
        echo $source_code_file >> $TEST_RESULT
        printf "%-4s %-25s %-80s %-80s \033[31m[%s]\033[0m\n" $all_num $model $source_code_file $run_result_file $result
    fi
    rm $run_result_file_tmp

    if [[ $IS_EXPORT_TEST_DETAIL_SUMMARY -eq 1 ]];then
        exportTestCase $all_num $model $source_code_file $run_result_file $result
    fi
}

printNotPassCase(){
    if [ ! -f "$TEST_RESULT" ]; then
    return 0
    fi
    printf "\033[31m[NotPassCase]"
    printf "%-60s %-60s\n" source_code_file err_nums
    awk '{count[$0]++;} END {for(i in count) {printf("%-60s %-60s\n",i,count[i])}}' $TEST_RESULT
    printf "\033[0m"
    rm $TEST_RESULT
}


start_time=`date +%s`
printf "%-4s %-25s %-80s %-80s %s\n" Num Model SourceCodeFile ResultFile Result

for((test_loop=1;test_loop<=$TEST_LOOP_NUM;test_loop++)); do {

    for model in ${TEST_MODELS[@]} ; do
        source_file_path=$TEST_PATH"/"$model
        for file in `ls $source_file_path`; do
            extension=${file##*.}
            if [ $extension == "ring" ]
            then
            autoTestAction $model $source_file_path $file
            fi
        done
        # printf "\n"
    done

}
done


# --------------------
printf "\n\n"
printf "\033[32m"
printf "[TestInfo]:\n"
printf "TEST_LOOP_NUM     = $TEST_LOOP_NUM\n" 
printf "TEST_RING_BIN     = $TEST_RING_BIN\n" 
printf "TEST_RING_OPTION  = $TEST_RING_OPTION\n" 
printf "TEST_RING_COMMAND = $TEST_RING_COMMAND\n" 
printf "TEST_COMMAND      = $TEST_COMMAND\n" 
printf "TEST_PATH         = $TEST_PATH\n"
printf "\033[0m"

# --------------------
printf "\n\n"
if [[ $succ_num -eq $all_num ]];then
    printf "\033[32m"
else
    printf "\033[33m"
fi
printf "[Result]:\n"
printf "Pass/All = %s/%s\n" $succ_num $all_num 
printf "NotTest  = %s\n" $not_test_num
printf "Fail     = %s\n" $fail_num
end_time=`date +%s`
runtime=$((end_time-start_time))
printf "Usetime  = %dS\n\n" $runtime
printf "\033[0m"


printNotPassCase



#
# 998-error-report 测试用例说明
# 测试方法  去除颜色控制字符
# ./bin/ring run ./test/998-error-report/error-004.ring 2>&1 | sed -r 's/\x1B\[([0-9]{1,2}(;[0-9]{1,2})?)?[m|K]//g'  > ./test/998-error-report/error-004.ring.result
# 
# 
# error-000.ring  使用未定义变量
# error-001.ring  使用未定义函数
# error-002.ring  重复定义全局变量
# error-003.ring  重复定义函数
# error-004.ring  重复 import package
# error-006.ring  定义self变量



# 
# 如何 测试 ring dump 修改的正确性
# 
# ./bin/ring dump ./test/008-class/class-method-001.ring