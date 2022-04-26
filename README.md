# C- Compiler Project

- [C- Compiler Project](#c--compiler-project)
  - [编译](#编译)
  - [小实验](#小实验)
    - [re_match](#re_match)
  - [preprocessor](#preprocessor)
    - [使用](#使用)
    - [结果](#结果)
  - [lexer](#lexer)
    - [使用](#使用-1)
    - [输出格式](#输出格式)

- [ ] 小实验
  - [x] re_match
  - [ ] LL(1)
- [x] preprocessor
- [ ] Lexer
  - [x] C++
  - [ ] flex
- [ ] Parser
  - [ ] C++
  - [ ] bison

> build by [xmake](https://github.com/xmake-io/xmake/)

> 注释在词法分析阶段处理

## 编译

本项目可用两种构建工具
- [xmake](https://xmake.io/#/zh-cn/guide/installation)
- [CMake](https://cmake.org/download/) 只支持 lexer 的编译 后续不适用

```bash
git clone https://github.com/HUGHNew/minus-c.git
cd minus-c
```

编译

```bash
# xmake
xmake
# CMake
mkdir build && cd build
cmake ..
make
```

## 小实验

### re_match

测试样例写在了 re_match/main.cpp 中

> 需要编译器支持 C++17 标准！！~~支持`std::string_view`就行~~

```bash
xmake run re_main
```

只会输出不通过的样例

## preprocessor

测试样例
- test/err.c
- test/pass_pre.c

### 使用

```bash
# 编译二进制
xmake b minus-preprocessor
# multiple files
./bin/minus-preprocessor test/pass_pre.c test/err.c
# or
xmake r minus-preprocessor ../test/pass_pre.c ../test/err.c
```

### 结果

预处理器会顺序处理输入的文件

如果注释正确 则会将注释替换为空格并写回文件 否则报错并中止

错误信息如下

```
../test/err.c: preprocessing error|msg:row:0 col:0       open comment
```

## lexer

### 使用

```bash
# a single file
./bin/minus-lexer test/gcd.cminus
# or
xmake run minus-lexer ../test/gcd.cminus
# multiple files
./bin/minus-lexer test/gcd.cminus test/hello.cminus test/error.cminus
# or
xmake run minus-lexer ../test/gcd.cminus ../test/hello.cminus ../test/error.cminus
```

### 输出格式

```
file:
lexemes
[error msg]
```
lexemes ::= lexeme lexemes
lexeme ::= `<'__name__',__type,(__line,__col)>`

- name 为 lexeme 内容
- type 为 lexeme 类型 只有四种
  - id
  - number
  - operator
  - keyword
- 行号和列号都是从1开始

