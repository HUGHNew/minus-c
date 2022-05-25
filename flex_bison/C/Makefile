cc=clang
cpp=clang++
lflag=-+
yacc=bison
lang=c

objs=minus.o minus_impl.o

minus: minus.l minus.y minus.h ${objs}
	${yacc} -L ${lang} -d "$@.y"
	lex -o "$@.lex.c" $<
	${cc} -o $@ "$@.lex.c" ${objs}
minus_impl.o: minus_impl.c
minus.o: minus.c
.PHONY:clean run

clean:
	-rm *lex.c* *.tab.* *.o minus.c
	-ls|grep -v "\."|grep -v Makefile|xargs rm