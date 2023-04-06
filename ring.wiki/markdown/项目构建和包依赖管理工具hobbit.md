# ```Ring``` 项目构建和依赖管理工具 ```hobbit```


在前面的wiki中，了解了 ring 如何去编译运行 单个ring源代码文件，如果要是源代码文件有多个，该怎么办呢，代码如何组织呢，工程如何构建呢，依赖如何管理呢。


在现代编程语言中，项目构建、依赖管理是如何解决的呢：

C/C++：make cmake
Go：go mod
Rust：cargo
Java：maven


在这里，为了方便的构建项目、管理依赖，ring提供了原生的管理工具 ```hobbit```，没错 hobbit是霍比特人🧑🏽‍🌾。

新建工程

```
hobbit new project
cd project

```


语法语义检查、检查依赖
```
hobbit check
```

构建chunk文件

```
hobbit build -o executer

```

```
ringc ./executer

```


直接执行工程

```
hobbit run
```
