#!/bin/bash

# 需要向下兼容，测试之前的所有测试用例
#

TEST_RING_BIN="./bin/ring"

TEST_PATH="./test"

TEST_MODELS=(
    "001-basic-type" 
    "001-basic-type-string"
    "002-operator" 
    "003-native-function" 
    "004-derive-function" 
    "005-control-flow" 
    "006-variable" 
    "007-array"
    "008-class" 
    "009-package" 
    "010-main-entry" 
    "011-global-variable" 
    "012-local-variable"
    )

NOT_TEST_FILES=(
  "./test/005-control-flow/for-range-000.ring"
  "./test/001-basic-type-string/string-003.ring"
  "./test/004-derive-function/function-021.ring"
  )

TEST_RESULT="./automated-testing.sh.result"

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

    $TEST_RING_BIN run $source_code_file > $run_result_file_tmp
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
    let all_num++
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

for i in {1..1}; do {

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


