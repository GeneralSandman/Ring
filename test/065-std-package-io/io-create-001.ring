
package main

import {
    fmt;
    debug;
    vm;
    os;
    io;
}


typedef class File {
    field int fd;
}

// 测试 exist/create/seek/read_all/write/close/remove 函数
@main
function main() {

    var string file_name = "./io-create-001.ring.result.tmp";
    var bool   exist;
    var int    fileid;
    var string content;
    var string content_tmp = "test-write-content";

    
    fmt::printf("test case [0][exist]----------\n");
    exist = io::exist(file_name);
    fmt::printf("file exist: {}\n", exist);
    debug::debug_assert(exist == false);


    fmt::printf("\ntest case [1][create]----------\n");
    fileid = io::create(file_name);
    fmt::printf("fileid: {}\n", fileid);
	debug::debug_assert(fileid != -1);


    fmt::printf("\ntest case [2][exist]----------\n");
    exist = io::exist(file_name);
    fmt::printf("file exist: {}\n", exist);
    debug::debug_assert(exist == true);


    fmt::printf("\ntest case [4][read_all]----------\n");
    content = io::read_all(fileid);
    fmt::printf("content={}\n", content);
    debug::debug_assert(content == "");


    fmt::printf("\ntest case [5][write]----------\n");
    io::write(fileid, content_tmp);


    fmt::printf("\ntest case [6][read_all]----------\n");
    io::seek(fileid, 0L, 0);
    content = io::read_all(fileid);
    fmt::printf("content={}\n", content);
    debug::debug_assert(content == content_tmp);

    
    // 不 seek 读取不到文件内容了
    fmt::printf("\ntest case [7][read_all]----------\n");
    content = io::read_all(fileid);
    fmt::printf("content={}\n", content);
    debug::debug_assert(content == "");


    io::close(fileid);

    
	io::remove(file_name);
    exist = io::exist(file_name);
    fmt::printf("file exist: {}\n", exist);
    debug::debug_assert(exist == false);
}
