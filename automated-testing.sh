#!/bin/bash

# 需要向下兼容，测试之前的所有测试用例

TEST_PATH="./test/beat"

pass_num=0
all_num=0


autoTestFunc(){
    source_code_file=$1"/"$2
    run_result_file=$1"/"$2".result"
    run_result_file_tmp=$1"/"$2".result.tmp"
    result=""


    ./bin/ring $source_code_file > $run_result_file_tmp
    diff $run_result_file $run_result_file_tmp

    if [[ "$?" -eq 0 ]];then
		result="PASS"
        let pass_num++
	else
		result="FAILED"
	fi
    printf "%-4s %-60s %-60s [%s]\n" $all_num $source_code_file $run_result_file $result
    let all_num++
    rm $run_result_file_tmp
}



printf "%-4s %-60s %-60s %s\n" num source_code_file run_result_file result

for model in "control" "function" "variable"
do

    source_file_path=$TEST_PATH"/"$model
    for file in `ls $source_file_path`; do
        extension=${file##*.}
        if [ $extension == "ring" ]
        then
        autoTestFunc $source_file_path $file
        fi
    done

done


printf "\n\n pass/all=%s/%s\n" $pass_num $all_num 
