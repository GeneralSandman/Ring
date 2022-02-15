#!/bin/bash

# 需要向下兼容，测试之前的所有测试用例

TEST_PATH="./test/beat"
TEST_VERSION="control"
# TEST_VERSION="function"
# TEST_VERSION="variable"
SOURCE_FILE_PATH=$TEST_PATH"/"$TEST_VERSION
num=1

autoTestFunc(){

    source_code_file=$SOURCE_FILE_PATH"/"$1
    run_result_file=$SOURCE_FILE_PATH"/"$1".result"
    run_result_file_tmp=$SOURCE_FILE_PATH"/"$1".result.tmp"

    ./bin/ring $source_code_file > $run_result_file_tmp
    diff $run_result_file $run_result_file_tmp

    result=""
    if [[ "$?" -eq "0" ]];then
		result="PASS"
	else
		result="FAILED"
	fi
    
    printf "%-7s %-30s %-30s %-30s\n" $num $source_code_file $run_result_file $result

    let num++

    rm $run_result_file_tmp
}

echo "\t \n"
printf "%-7s %-30s %-30s %-30s\n" num source_code_file run_result_file result
for file in `ls $SOURCE_FILE_PATH`; do
    extension=${file##*.}
    if [ $extension == "ring" ]
    then
    autoTestFunc $file
    fi

done