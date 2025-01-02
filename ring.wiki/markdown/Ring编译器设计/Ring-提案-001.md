# Proposal: 协程

Author(s): GeneralSandman

First created: 2024-07-29

Last updated: 2024-07-31

Status: Draft/Design/Release

Discussion at https://github.com/GeneralSandman/Ring/issue/NNNNN.

## Abstract

Ring语言提案001，主要讨论和调研 协程的实现，和用户编写代码的形式。

## Background

### 2.1 Golang协程实现

Golang协程和线程区别：
https://www.cnblogs.com/yuhaohao/p/15421400.html

Go的CSP并发模型实现：
https://www.cnblogs.com/sunsky303/p/9115530.html


Callback 与 Coroutine 协程概念说明
https://aaaaaaron.github.io/2019/10/09/Callback%E4%B8%8E-Coroutine-%E5%8D%8F%E7%A8%8B%E6%A6%82%E5%BF%B5%E8%AF%B4%E6%98%8E/


GO.SETMAXPROCS() 是干什么的

https://www.reddit.com/r/golang/comments/199954n/what_is_gomaxprocs_actually_used_for/


### 2.2 Lua协程实现

Lua协程使用：
https://www.runoob.com/lua/lua-coroutine.html


可以参见lua的例子：



1. 需要深度了解一下 Lua编译器中 LuaState各种结构的逻辑
2. 深度了解 协程切换，需要做什么工作


### 2.3 Javascript协程实现


## Proposal


### A. 关于Ring中协程该如何实现


1. 采取有栈协程
2. 给ring的协程起一个好听的名字和关键字

首先给出一个例子，在ring中如何编写开启一个协程。

因为目前现在还不支持匿名函数，所以当前可以参考golang的使用方式：

```ring

fn test1() {
    fmt::printf("test 1");

    test2();
}

fn test2() {
    fmt::printf("test 2");
}

fn main() {

    var int64 co_id;

    // 开启一个协程
    // 目前还不能给test1 传递参数
    // 创建成功之后获得一个 协程ID
    co_id = co_create(test1);

    // 获取协程的相关信息
    co_

    // 等待协程完成
    // 需要协程ID
    co_wait(co_id);

}
```



- 使用 wait 开启一个协程
- 使用 wait 等待所有的协程完成


关于内部实现和用户使用
1. 用户通过ring编程进行读写IO，所有的操作都是非阻塞的，也就是
   - 阻塞的IO 包括 read write send recev fgetc
2. 用户不需要关心协程所有权的释放和抢占，有Ring-Co-Scheduler实现协程调度
3. 如果用户使用了读写IO，他会立即将IO的事件注册到Epoll中，当IO事件发生时，会通过Epoll机制从内核通知到Ring-Co-Scheduler，scheduler会唤醒对应的协程，协程会继续执行。
4. 如果用户没有使用读写IO，schedler会给每个协程分配一个时间片，然后一次调度每个不同的协程。
5. 内部实现
   1. co_id = co_create(); // 创建一个协程
   2. co_yield(any)        // 某个协程刮起
   3. co_resume(co_id)     // 恢复一个协程
   4. co_status(co_id)     // 查看一个协程的状态
   5. co_list()            // 返回目前所有挂起和running的协程列表
6. 启动双线程，
   - 一个线程 epoll进行事件监听，调度线程
   - 另一个线程进行用户态代码的执行（这样有个好处就是，我可以设置一个golang的的线程数量 ）
7. 如何设计协程切换

## Rationale

[A discussion of alternate approaches and the trade offs, advantages, and disadvantages of the specified approach.]

### 关于协程的语法

1. 创建一个协程

由于当前还不支持匿名函数，所有得通过关键字来创建协程：
```ring
launch func_name(); // 创建一个协程


// 当然，创建一个协程可以获得一个协程ID
// 协程ID是唯一的
var int64 co_id;
co_id = launch func_name();


// 协程创建完成之后，并不会立即运行，
```


a. 这里还有个隐式概念，那就是通过 main()函数，其实会启动一个 Main协程
b. Main协程是所有协程的根协程，所有协程都是由它衍生出来的
c. 它负责执行main函数中的代码。
d. 当main函数返回时,主协程结束,整个程序也随之结束。
e. 如果main函数中创建了其他协程,但主协程先于这些协程结束,则整个程序也会结束。 


2. 如何唤醒一个协程

```ring
// 协程创建完成之后，并不会立即运行，需要手动resume
// 指定协程ID
// resume 之后，当前协程会挂起，目标协程会恢复运行
resume co_id;



// 还未想好：
// 唤醒一个协程之后，如果协程能够正确的执行完成
// 如何获取协程的返回值
// resume 可以有个返回值
```

a. Main协程会自动执行的，用户不需要关心
b. 所有用户手动创建的协程都需要 `resume` 来调度运行
c. 当前协程 resume 别的协程之后，当前协程会被挂起，目标协程会恢复运行


3. 协程挂起


```ring

fn func_main() -> (string) {

    // do some work

    yield;

    // do some work

    return "finish";
}

// yield 跟着一个参数，这个参数可以返回
yield any; // 这里还没设计好，因为Ring是一个静态类型系统，这里得保证任何类型都能被接收到
```


```ring
fn main() {
    
    // create
    co_id = launch func_main();

    resume co_id; // func_main 会运行到 yield


    resume co_id; // func_main 会从yield继续运行到 结束
}
```

a. yield会暂时中断当前协程的执行,并将控制权交给协程调度器。
b. 协程调度器会选择一个准备就绪的协程继续执行。这个被选中的协程可能就是当前被挂起的协程,也可能是其他协程。
c. 当该协程再次被选中恢复执行时,yield语句会返回,协程会从中断的地方继续执行。
e. yield不能直接挂起其他协程。如果需要挂起其他协程,需要通过协程调度器来实现,例如在一个协程中创建并启动另一个协程。
f. 还有个隐式行为，那就是 yield会将调度权返回给 resume的协程；也就是 Main协程不能 yield，否则程序会崩溃。

4. 协程完成

```ring
```
a. 当执行完成一段函数的时候，一个协程就会完成，这个协程会被销毁，协程ID不再合法，
b. 如果继续操作一个 不合法的协程ID则会报错


5. 协程之间如何传递数据


6. 给出一个完成的例子

```ring

package main

import {
    fmt;
}

fn job() {

    fmt::println("job::doit1");

    yield;

    fmt::println("job::doit2");

    return;
}


fn main() {
    var int64 co_id;

    // 创建协程但不运行
    co_id = launch job();
    fmt::printf("launch a coroutine, co_id={}\n", co_id);

    fmt::println("main::1");
    // 启动协程
    // 当前协程会挂起，目标协程会恢复运行
    // 当目标协程挂起时，当前协程恢复运行
    resume co_id;

    fmt::println("main::2");
    // 继续启动协程
    resume co_id;


    fmt::println("main::3");
    // 这个时候协程已经完成，如果继续resume则无效果
    resume co_id;

    fmt::println("main::end");
}

```

程序输出：

```shell
launch a coroutine, co_id=1
main::1
job::doit1
main::2
job::doit2
main::3
main::end
```




//--boot
launch(main, string[]{"1", "2"});

fn main() {
    co_id = launch(job_action);
}

### 2024-08-10

// 1. 先不用管 main函数, 先考虑用户行为的 launch
// 3. 先不考虑 resume yield
// 3. 先只考虑 launch 和协程结束
// - launch 中不支持传递函数的参数
// - 协程结束: call_info为空



协程引起这几个测试不太正确

多了 一层 `$ring!start()`

```
[NotPassCase]source_code_file                                             err_nums                                                    
./test/060-std-package-debug/debug-stack-003.ring            1                                                           
./test/060-std-package-debug/debug-stack-004.ring            1                                                           
./test/060-std-package-debug/debug-stack-005.ring            1                                                           
./test/060-std-package-debug/debug-stack-006.ring            1                                                           
./test/060-std-package-debug/debug-stack-007.ring            1                                                           
./test/060-std-package-debug/debug-stack-008.ring            1                                                           
./test/060-std-package-debug/debug-stack-009.ring            1                                                           
./test/060-std-package-debug/debug-stack-000.ring            1  
```


## Compatibility

[A discussion of the change with regard to the
[compatibility guidelines](https://go.dev/doc/go1compat).]

## Implementation

[A description of the steps in the implementation, who will do them, and when.
This should include a discussion of how the work fits into [Go's release cycle](https://go.dev/wiki/Go-Release-Cycle).]

## Open issues (if applicable)

[A discussion of issues relating to this proposal for which the author does not
know the solution. This section may be omitted if there are none.]