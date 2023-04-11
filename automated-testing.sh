#!/bin/bash

# 需要向下兼容，测试之前的所有测试用例

TEST_PATH="./test"

TEST_RESULT="./automated-testing.sh.result"

pass_num=0
all_num=0


autoTestFunc(){
    model=$1
    source_code_file=$2"/"$3
    run_result_file=$2"/"$3".result"
    run_result_file_tmp=$2"/"$3".result.tmp"
    result=""


    ./bin/ring run $source_code_file > $run_result_file_tmp
    diff $run_result_file $run_result_file_tmp

    if [[ "$?" -eq 0 ]];then
		result="PASS"
        let pass_num++
	else
		result="FAILED"
        echo $source_code_file >> $TEST_RESULT
	fi
    printf "%-4s *%-15s %-60s %-60s [%s]\n" $all_num $model $source_code_file $run_result_file $result
    let all_num++
    rm $run_result_file_tmp
}


printNotPassCase(){
    if [ ! -f "$TEST_RESULT" ]; then
    return 0
    fi
    echo "[NotPassCase]"
    printf "%-60s %-60s\n" source_code_file err_nums
    awk '{count[$0]++;} END {for(i in count) {printf("%-60s %-60s\n",i,count[i])}}' $TEST_RESULT
    rm $TEST_RESULT
}


printf "%-4s %-16s %-60s %-60s %s\n" num model source_code_file run_result_file result

for i in {1..1}; do {

    for model in "001-basic-type" "002-operator" "003-native-function" "004-derive-function" "005-control-flow" "006-variable" "008-class" ; do
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


printf "\n\n[pass/all=%s/%s]\n\n" $pass_num $all_num 


printNotPassCase

