//
// File:    io.ring
// Author:  GeneralSandman - generalsandman@163.com
// CDate:   2023-10-08
// UDate:   2023-10-08
//

package io

import {
	fmt;
}

global {

}


// typedef class File {
//     field int fd;

// 	method read_all() -> (string) {
// 	    return read_all(self.fd);
// 	}

// 	method write(var string buffer) {
// 	    write(self.fd, buffer);
// 	}

// 	method close() {
// 	    close(self.fd);
// 	}
// }

@native
function exist(var string path) -> (bool);

@native
function open(var string path) -> (int);

@native
function create(var string path) -> (int);

@native
function seek(var int fd, var int64 offset, var int whence);

@native
function read_all(var int fd) -> (string);

@native
function write(var int fd, var string buffer);

@native
function close(var int fd);

@native
function remove(var string path);

