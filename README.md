# Ring


## ```Ring```语言的特性与展望

- 静态类型 (Static Typing) 语言；（本人讨厌动态类型语言，写时一直爽，改时火葬场）
- 解释执行
- 暂不支持垃圾回收GC
- 暂不支持面向对象
- import 导包
- 支持bind 绑定函数
- auto类型
- lambda表达式

## 为什么以```Ring```命名

大学的时候反反复复看了四遍指环王、霍比特人系列的电影，超级喜欢中土世界，所以 ```Ring``` 取自 ```The Lord of the Rings```。

- 至尊魔戒（*One Ring*）
- 亦即是支配魔戒（*Ruling Ring*）
- 大魔戒（*The Great Ring*，或译为统御魔戒）
- 强力魔戒（*Great Ring of Power*）
- 魔戒（*The Ring*）

至尊魔戒上文字是以黑暗语（Black Speech）写成的谈格瓦文字（Tengwar），象征至尊魔戒的力量可以驾驭其他统御魔戒。

在平常，至尊魔戒的表面平滑，毫无特色，但在火炎燃烧时，戒指内外也会显现如火的文字：

```

Ash nazg durbatulûk, ash nazg gimbatul, ash nazg thrakatulûk, agh burzum-ishi krimpatul.

魔戒全属至尊御，至尊指引诸魔戒，至尊魔戒唤众戒，众戒归一黑暗中。

```



Reference wikipedia https://zh.wikipedia.org/wiki/%E8%87%B3%E5%B0%8A%E9%AD%94%E6%88%92


## 如何使用源代码&运行一个HelloWorld

[如何运行 HelloWorld](./doc/using.md)

## Ring语言语法规范

[Ring语法语义](./doc/语法概念.md)

## 历史版本功能

| 时间       | 版本   | 特性                                                                                                                         |
| ---------- | ------ | ---------------------------------------------------------------------------------------------------------------------------- |
| -          | v0.0.6 | string 变量/常量 ‘+’ 拼接运算符。支持自定义函数。                                                                            |
| 2022-01-26 | v0.0.5 | 编译错误时，打印当前行的内容、并提示错误编译的信息。                                                                         |
| 2022-01-26 | v0.0.4 | int/double/string 变量的赋值操作，int/double 四则运算，支持打印 int/double/string 变量/常量 ，添加自动化测试脚本             |
| 2022-01-25 | v0.0.3 | 支持解析 + - * / 运算法表达式，和 int string 变量的赋值操作，支持打印 int变量、string变量、string常量，DEBUG日志支持颜色分类 |
| 2022-01-20 | v0.0.2 | 支持解析 string变量定义，string变量赋值，print打印string常量                                                                 |
| 2022-01-19 | v0.0.1 | 支持解析print函数、但是还没有调用成功                                                                                        |
| 2022-01-18 | v0.0.0 | 支持解析 注释 string变量定义和复制                                                                                           |

## TODO List


## Contributer

