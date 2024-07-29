# Proposal: 协程

> 提出人：GeneralSandman
> 
> 提出时间：2024-07-23
> 
> 修订时间：2024-07-23
> 

## 1. 介绍

Ring语言提案001，主要讨论和调研 协程的实现，和用户编写代码的形式。

## 2. 调研

### 2.1 Golang的协程

Golang协程和线程区别：
https://www.cnblogs.com/yuhaohao/p/15421400.html

Go的CSP并发模型实现：
https://www.cnblogs.com/sunsky303/p/9115530.html


Callback 与 Coroutine 协程概念说明
https://aaaaaaron.github.io/2019/10/09/Callback%E4%B8%8E-Coroutine-%E5%8D%8F%E7%A8%8B%E6%A6%82%E5%BF%B5%E8%AF%B4%E6%98%8E/


GO.SETMAXPROCS() 是干什么的

https://www.reddit.com/r/golang/comments/199954n/what_is_gomaxprocs_actually_used_for/


### 2.1 Lua协程实现


1. 需要深度了解一下 Lua编译器中 LuaState各种结构的逻辑
2. 深度了解 协程切换，需要做什么工作


### A. 关于Ring中协程该如何实现


1. 采取有栈协程
2. 给ring的协程起一个好听的名字和关键字

首先给出一个例子，在ring中如何编写开启一个协程。

因为目前现在还不支持匿名函数，所以当前可以参考golang的使用方式：

```ring

function test1() {
    fmt::printf("test 1");

    test2();
}

function test2() {
    fmt::printf("test 2");
}

function main() {

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