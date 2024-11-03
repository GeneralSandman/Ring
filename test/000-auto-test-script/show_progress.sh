#!/bin/bash

show_progress() {
    prefix_str=$1
    total_num=$2
    curr_num=$3
    progress_length=100

    # 计算进度百分比
    percent=$((curr_num * 100 / total_num))

    # 计算进度条中已完成的部分和剩余部分
    completed_length=$((progress_length * curr_num / total_num))
    remaining_length=$((progress_length - completed_length))

    # 构建进度条
    progress_bar=$(printf "%-${completed_length}s" "#" | tr ' ' '#')$(printf "%-${remaining_length}s" " ")

    # 输出进度条
    printf "\r%s[%s] %d%%" "$prefix_str" "$progress_bar" "$percent"
    if [ "$curr_num" -eq "$total_num" ]; then
        printf "\n"
    fi
}

# 示例：模拟进度更新
# total=30
# for i in $(seq 0 $total); do
#     show_progress $total $i
#     sleep 0.1  # 模拟处理时间
# done