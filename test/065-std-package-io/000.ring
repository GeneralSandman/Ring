
package main

import {
    fmt;
    debug;
    vm;
    os;
    io;
}


typedef File = class {
    var int fd;
}

fn main() {
    var int fileid = io::open("/Users/zhenhuli/Desktop/Ring/test/065-std-package-io/000.ring");

    // var string content = io::read_all(fileid);  // FIXME: 这样写存在bug, 会调用两次

    var string content;
    content = io::read_all(fileid);

    fmt::println_string(content);

    io::close(fileid);
}
