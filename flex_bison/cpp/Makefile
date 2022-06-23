cpp=clang++
cc=clang
objs=minus.lex.o minus.tab.o
YFLAGS=-vd

minus_cpp: ${objs}
	cpp -o $@ ${objs}
minus.lex.o: minus.lex.c minus.tab.cc minus.cpp.h
minus.tab.o: minus.tab.cc minus.cpp.h

minus.lex.c: minus.l
minus.tab.cc minus.tab.hh: minus.yy

clean:
	@rm minus_cpp
	@rm minus.lex.* minus.tab.*