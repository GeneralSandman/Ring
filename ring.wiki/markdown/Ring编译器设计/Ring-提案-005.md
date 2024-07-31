# Proposal: 枚举

Author(s): GeneralSandman

First created: 2024-07-29

Last updated: 2024-07-31

Status: Draft/Design/Release

Discussion at XXX.

## Abstract

[A short summary of the proposal.]

## Background

[An introduction of the necessary background and the problem being solved by the proposed change.]

## Proposal

1. 先给出几个例子定义枚举

```ring
enum {
    string stdin = "stdin";
    string stdout = "stdout";
    string stderr = "stderr";
};
```


枚举需要能被这样使用：
1. 支持用户定义
2. 支持用户formate输出
3. 只用通过package导出和访问
4. 支持比较

## Rationale

在这里，设计一下enum的相关语法

1. 定义一个 enum

语法
```
enum <basic-type> <Enum-Type> {
    <Enum-Name> = <value>;
    <Enum-Name> = <value>;
}
```

例如：string类型的枚举
```ring
enum string Color {
    Red = "red";
    Green = "green";
    Blue = "blue";
};
```

1. 使用 enum

```ring
fn main() {
    fmt::println(Color::Red);
}
```

3. 最终参数传递函数的时候，会转换成对应的底层基础类型 bool/int/int64/double/string


限制：
1. enum 目前类型只能是  bool/int/int64/double/string
2. enum 初始化的值必须是常量  `Red = "Red";`  `Red = global_variable; // 编译错误`
   1. 因为需要在编译过程就就能确定常量的值
3. enum 的值必须是唯一的
4. enum 最终的类型 为 基础类型

## Compatibility

[A discussion of the change with regard to the
[compatibility guidelines](https://go.dev/doc/go1compat).]

## Implementation

[A description of the steps in the implementation, who will do them, and when.
This should include a discussion of how the work fits into [Go's release cycle](https://go.dev/wiki/Go-Release-Cycle).]

## Open issues (if applicable)

[A discussion of issues relating to this proposal for which the author does not
know the solution. This section may be omitted if there are none.]