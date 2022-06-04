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
  - [Flex/Bison](#flexbison)
    - [lexer](#lexer-1)
    - [parser](#parser)
  - [测试样例](#测试样例)

- [x] 小实验
  - [x] re_match
- [x] preprocessor
- [x] Lexer
  - [x] C++
  - [x] flex
- [ ] Parser
  - [ ] C++
  - [ ] bison
    - [x] C

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

> 本来是用来在flex使用的预处理的 但现在在flex中直接处理了注释 所以没有使用了

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


## Flex/Bison

路径: `flex_bison/C`

所需工具链:
- flex
- bison
- make
- gcc/clang/mingw-gcc/msvc/..

> 使用 Makefile/Make 作为构建系统
> 
> 这里使用 `clang` 作为 C语言编译器 可以通过更改 [Makefile](flex_bison/C/Makefile) 中的 `cc` 变量来切换为 `gcc` 等编译器

### lexer

也可以使用 flex 构建的 lexer

需要把[lex文件](flex_bison/C/minus.l)中的 line 10:`#define debug 0` 中的 0 改为 1

```bash
# 编译
make
# 编译结果为 ./minus
# 运行
./minus ../../test/gcd.cminus ../../test/s.cminus
./minus ../../test/gcd.cminus
```
lexeme 格式 `type:<value> (row,column)`

### parser

BNF 文法:<c-minus.bnf>  
bison 版本的BNF文法:<flex_bison/C/minus.bison.bnf> 没有包含第一条规则

> 头文件:[minus.h](flex_bison/C/minus.h)

> 源文件:[minus_impl.c](flex_bison/C/minus_impl.c)

利用 [Python 脚本](flex_bison/C/preprocess.bnf.bison.py) 生成普遍的匹配动作

```bash
cd flex_bison/C/
python preprocess.bnf.bison.py >> minus.head.y
# 生成基础的bison文件
```

假定语法为

```bnf
A' -> a A
A -> a
```

默认语法树输出格式如下(`<space>`为空格)
```bnf
a
<space><space>a
```
可以通过定义<flex_bison/C/minus_impl.c>文件中的`PARSE_RULE`的宏来控制是否输出语法规则(存在时输出) 下面是语法规则时的输出(将该项并入了Makefile中)
```
A' -> a A
<space><space>a
<space><space>A -> a
<space><space><space><space>a
```

切换编译目标时 需要 `make clean`

```bash
# 编译
make
# 等于 make minus
# 编译结果为 ./minus 不会输出语法规则
make minus_rule
# 编译结果为 ./minus_rule 会输出语法规则
# 运行
./minus ../../test/gcd.cminus
./minus_rule ../../test/gcd.cminus
```

若出现语法错误则中止该文件的分析 并输出错误位置 如下示例
```
2,13: error:syntax error
2,13: error:parse error when process file:../../test/error.cminus
```

## 测试样例

正确的测试样例
- gcd.cminus
- s.cminus
- sort.cminus

其他都是带错误的样例