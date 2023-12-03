#!/bin/bash

# 需要向下兼容，测试之前的所有测试用例
#

# 测试的可执行文件
TEST_RING_BIN="./bin/ring"

# 要测试的文件夹
TEST_PATH="./test"
TEST_MODELS=(
    "001-bool"
    "002-int"
    "003-double"
    "004-string"

    "001-basic-type" 
    "001-basic-type-string"

    "002-operator" 
    "003-native-function" 
    "004-derive-function" 
    "006-variable" 
    "007-array"
    "008-class" 
    "010-main-entry" 
    "011-global-variable" 
    "012-local-variable"
    "013-gc"

    "020-array-bool"
    "021-array-int"
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
    )

# 跳过测试的case
NOT_TEST_FILES=(
  "./test/004-derive-function/function-021.ring" # 函数传递 var int... int_value_list
  "./test/013-gc/gc-000.ring" # 数组的地址  如何进行 自动化测试
  "./test/008-class/class-001.ring" # 目前不支持 method


  "./test/024-array-class/for-access-000.ring" 
  # global_job_array_0[index].Running = true; 不支持给数组中元素的成员变量进行赋值

  "./test/002-operator/arith-oper-002.ring"
  # double 数值比对, 存在bug
  )

# 测试的结果文件
TEST_RESULT="./automated-testing.sh.result"

# 测试的轮数, 用于多次执行
TEST_LOOP_NUM=1

not_test_num=0
pass_num=0
all_num=0

isNotTestFile(){
    for i in ${NOT_TEST_FILES[@]} ; do
      [ "$i" == "$1" ] && return 1
    done
    return 0
}

autoTestFunc(){
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
        printf "%-4s *%-20s %-80s %-80s \033[33m[%s]\033[0m\n" $all_num $model $source_code_file $run_result_file $result
        return
    fi

    let all_num++


    $TEST_RING_BIN run $source_code_file &> $run_result_file_tmp
    if [[ "$?" -ne 0 ]];then
        result="FAILED"
        echo $source_code_file >> $TEST_RESULT
        printf "%-4s *%-20s %-80s %-80s \033[31m[%s]\033[0m\n" $all_num $model $source_code_file $run_result_file $result
        return
    fi
    
    diff $run_result_file $run_result_file_tmp

    if [[ "$?" -eq 0 ]];then
        result="PASS"
        let pass_num++
        printf "%-4s *%-20s %-80s %-80s \033[32m[%s]\033[0m\n" $all_num $model $source_code_file $run_result_file $result
    else
        result="FAILED"
        echo $source_code_file >> $TEST_RESULT
        printf "%-4s *%-20s %-80s %-80s \033[31m[%s]\033[0m\n" $all_num $model $source_code_file $run_result_file $result
    fi
    rm $run_result_file_tmp
}

printNotPassCase(){
    if [ ! -f "$TEST_RESULT" ]; then
    return 0
    fi
    echo "\033[31m[NotPassCase]"
    printf "%-60s %-60s\n" source_code_file err_nums
    awk '{count[$0]++;} END {for(i in count) {printf("%-60s %-60s\n",i,count[i])}}' $TEST_RESULT
    echo "\033[0m"
    rm $TEST_RESULT
}


start_time=`date +%s`
printf "%-4s *%-20s %-80s %-80s %s\n" num model source_code_file run_result_file result

for((test_loop=1;test_loop<=$TEST_LOOP_NUM;test_loop++)); do {

    for model in ${TEST_MODELS[@]} ; do
        source_file_path=$TEST_PATH"/"$model
        for file in `ls $source_file_path`; do
            extension=${file##*.}
            if [ $extension == "ring" ]
            then
            autoTestFunc $model $source_file_path $file
            fi
        done
        printf "\n"
    done

}
done


printf "\n\n"
if [[ $pass_num -eq $all_num ]];then
    printf "\033[32m"
else
    printf "\033[33m"
fi
printf "[Result]:\n"
printf "Pass/All = %s/%s\n" $pass_num $all_num 
printf "NotTest  = %s\n" $not_test_num
end_time=`date +%s`
runtime=$((end_time-start_time))
printf "Usetime:%4ds\n\n" $runtime
printf "\033[0m"


printNotPassCase


