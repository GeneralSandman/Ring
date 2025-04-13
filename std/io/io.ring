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


@native
fn exist(var string path) -> (bool);

@native
fn open(var string path) -> (int);

@native
fn create(var string path) -> (int);

@native
fn seek(var int fd, var int64 offset, var int whence);

@native
fn read_all(var int fd) -> (string);

@native
fn write(var int fd, var string buffer);

@native
fn close(var int fd) -> (int);

@native
fn remove(var string path);

