
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

@main
function main() {
    var string file_name = "./test/065-std-package-io/io-open-000.ring";
    var bool   exist;
    var int    fileid;
    var string content;
    var string content_tmp = "test-write-content";

    fmt::printf("test case [0][open]----------\n");
    fileid = io::open(file_name);
	debug::assert(fileid != -1);

    fmt::printf("test case [1][read_all]----------\n");
    content = io::read_all(fileid);
    fmt::println_string(content);

    io::close(fileid);
}
