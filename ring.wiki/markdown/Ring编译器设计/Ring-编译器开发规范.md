# Ring 编译器开发规范

- 更新时间：*2023-10-21*

## 1. Ring Compiler coding style Guidelines

This is a short document describing the preferred coding style for the ring compiler. Coding style is very personal, and I won't force my views on anybody, but this is what goes for anything that I have to be able to maintain, and I'd prefer it for most other things too. Please at least consider the points made here.

Anyway, here goes:

### 1.1 Formatting with Clang-Format:

- Before pushing code to the origin repository, ensure that it is formatted using Clang-Format. Clang-Format automatically applies predefined rules, enhancing code readability.
- The *.clang-format* file defines the basic code style, including the indentation rules.

### 1.2 Struct Naming:

- Don't use *class*, only use *struct*.
- Use Upper Camel Case (PascalCase) for struct names. This convention capitalizes the first letter of each word in the name, without underscores or hyphens.
    - e.g. `struct PackageUnit{};`
- Must use *typedef* keyword to redefine the name of struct type.
    - You can omit keyword `struct` when you definite variable of `struct XX`.
    - e.g. `typedef struct PackageUnit PackageUnit;`
    - e.g. `PackageUnit main_unit;`

### 1.3 Variable Naming:

- Utilize Snake Case for variable names. Snake case involves writing all lowercase letters and separating words with underscores. This convention enhances the clarity and readability of variable names.

By following these guidelines, you can create a consistent and easily understandable codebase. Remember to communicate these conventions to your team members and enforce them during code reviews to maintain uniformity.


### 1.4 Function Definition:

When the function signature is too long, you need flod it.
In this case, you need add a empty line at the beginning of block.
This style is beautiful.
e.g. The thired line is must empty.

```
void rvm_add_static_variable(Package_Executer*  executer,
                             RVM_RuntimeStatic* runtime_static) {

    debug_log_with_white_coloar("\t");

    unsigned int size    = executer->global_variable_size;
    runtime_static->size = size;
    runtime_static->data = (RVM_Value*)mem_alloc(NULL_MEM_POOL, size * sizeof(RVM_Value));
}
```


If you not flod function signature, not need add a empty line.

```
void ring_bytecode_dump(Package_Executer* executer, FILE* output) {
    debug_log_with_darkgreen_coloar("\t");
}
```


### 1.5 Commenting


Comments are good, but there is also a danger of over-commenting. **NEVER** try to explain **HOW** your code works in a comment: it's much better to write the code so that the working is obvious, and it's a waste of time to explain badly written code.

Generally, you want your comments to tell **WHAT** your code does, not HOW.

The preferred style for long (multi-line) comments is:
```
/*
 * This is the preferred style for multi-line
 * comments in the Linux kernel source code.
 * Please use it consistently.
 *
 * Description:  A column of asterisks on the left side,
 * with beginning and ending almost-blank lines.
 */
```


It's also important to comment data, whether they are basic types or derived types. To this end, use just one data declaration per line (no commas for multiple data declarations). This leaves you room for a small comment on each item, explaining its use.

https://www.kernel.org/doc/html/latest/process/coding-style.html


### 1.6 Using C++17 

https://en.cppreference.com/w/cpp/17



## 2.Ring Github Source Code Repository


### 2.1 Repository Summary


### 2.2 IDE

### 2.2 How to update *complie_commands.json*


### 2.3 How to use *VimSpector* Debugging



