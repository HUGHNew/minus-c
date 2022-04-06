# C- Compiler Project

- [ ] 小实验
  - [x] re_match
- [x] Lexer
- [ ] Parser

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

> 需要编译器支持 C++17 标准！！

```bash
xmake run re_main
```

只会输出不通过的样例

## lexer

### 使用

```bash
# a single file
./bin/minus-lexer test/gcd.cminus
# multiple files
./bin/minus-lexer test/gcd.cminus test/hello.cminus test/error.cminus
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

