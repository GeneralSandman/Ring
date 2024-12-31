# Proposal: 标准库

Author(s): GeneralSandman

First created: 2024-07-29

Last updated: 2024-07-31

Status: Draft/Design/Release

Discussion at https://github.com/GeneralSandman/Ring/issue/NNNNN.

## Abstract

1. io/os 相关标准库
2. 如何实现枚举 如：
`O_RDONLY` `O_WRONLY` `O_RDWR` `O_APPEND` `O_CREATE` `O_EXCL` `O_SYNC` `O_TRUNC`
3. 还要实现位操作，如：`O_RDWR|O_CREATE|O_TRUNC`

## Background

关于Lua中是如何实现调用C语言 标准IO的：

```lua
```

## Proposal

关于c语言标准的IO读写函数，会返回一个FILE*， 但是Ring是一个静态类型系统，所以如何实现包装文件读写函数：


1. 关于Ring的编程

```ring
    var string content;

    var io.File file;

    file = io.open("file-path"); // 打开文件，获得一个 fileIO

    // 写法1, read_all 是io.File的method
    content = file.read_all();
    // 写法2, read_all 是io-package中的function
    content = io.read_all(file);

    fmt::println(content);

    // 写法1，close 是io.File的method
    file.close();
    // 写法2，close 是io-package中的function
    io.close(file);
```



1. file 变量中保存着c语言的文件IO结构体：`FILE*`
2. file.ReadAll() 则会调用内部的实现，先找到 `FILE*`, 然后调用read函数
3. 看上述源码，这里有两种写法，基于目前Ring的编译器实现，倾向于方式 2
4. 在打开文件的时候，通常有这几种mode，需要将枚举实现
```
const (
	// Exactly one of O_RDONLY, O_WRONLY, or O_RDWR must be specified.
	O_RDONLY int = syscall.O_RDONLY // open the file read-only.
	O_WRONLY int = syscall.O_WRONLY // open the file write-only.
	O_RDWR   int = syscall.O_RDWR   // open the file read-write.
	// The remaining values may be or'ed in to control behavior.
	O_APPEND int = syscall.O_APPEND // append data to the file when writing.
	O_CREATE int = syscall.O_CREAT  // create a new file if none exists.
	O_EXCL   int = syscall.O_EXCL   // used with O_CREATE, file must not exist.
	O_SYNC   int = syscall.O_SYNC   // open for synchronous I/O.
	O_TRUNC  int = syscall.O_TRUNC  // truncate regular writable file when opened.
)
```



### 关于 `std/io/io.ring` 的文件内容

```ring
//
// File:    io.ring
// Author:  GeneralSandman - generalsandman@163.com
// CDate:   2023-10-08
// UDate:   2023-10-08
//

package io

import {

}

global {

}



@native
fn open(var string path) -> (File);

@native
fn read_all(var File file) -> (string);

@native
fn write(var File file, var string buffer);

@native
fn seek(var File fild, long offset, int whence);

@native
fn close(var File file);

typedef class File {
	@native-c-field
	field FILE* _file;
};


```

1. 方便用户找到io-package相关的函数原型
1. 定义了封装C语言内部的 `FILE*` 结构体
2. 定义了 函数：
   1. open read_all write close



## Rationale

[A discussion of alternate approaches and the trade offs, advantages, and disadvantages of the specified approach.]

## Compatibility

[A discussion of the change with regard to the
[compatibility guidelines](https://go.dev/doc/go1compat).]

## Implementation

[A description of the steps in the implementation, who will do them, and when.
This should include a discussion of how the work fits into [Go's release cycle](https://go.dev/wiki/Go-Release-Cycle).]

## Open issues (if applicable)

[A discussion of issues relating to this proposal for which the author does not
know the solution. This section may be omitted if there are none.]