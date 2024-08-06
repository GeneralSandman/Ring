
#!/bin/bash

# parse bash arguments
# ./parse_args.sh TEST_RING_BIN=1 TEST_MODELS=2,3 
# TEST_RING_BIN 字符串
# TEST_MODELS   字符串数组，逗号分隔
parse_args() {
    for arg in "$@"
    do
        case $arg in
            TEST_RING_BIN=*)
                ARG_TEST_RING_BIN="${arg#*=}"
                shift
                ;;
            TEST_MODELS=*)
                IFS=',' read -ra ARG_TEST_MODELS <<< "${arg#*=}"
                shift
                ;;
            *)
                echo "Unknown parameter: $arg" >&2
                ;;
        esac
    done

    # 将解析后的参数值存储到全局变量中
    export ARG_TEST_RING_BIN
    export ARG_TEST_MODELS
}