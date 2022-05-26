cc=clang
cpp=clang++
lflag=-+
lang=c
YFLAGS=-L ${lang} -d

objs=minus.o minus.lex.o  minus_impl.o

minus: ${objs}
	${cc} -o $@ ${objs}
minus_rule: ${objs}
	${cc} -c -o minus_impl.o -D PARSE_RULE minus_impl.c
	${cc} -o $@ ${objs}
minus.tab.c: minus.y minus.h
minus.lex.o: minus.lex.c
minus.lex.c: minus.l minus.h
	lex -o $@ $<
minus_impl.o: minus_impl.c
minus.o: minus.c
.PHONY:clean
clean:
	-@rm *lex.c* *.tab.* *.o minus.c minus minus_rule