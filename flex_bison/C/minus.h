#include<stdio.h>
/* interface to the lexer */
extern int yylineno; /* from lexer */
extern FILE* yyin; /* from lexer */
extern int yylex(); /* from lexer */
extern int yyparse(); /* from parse */
void yyerror(char *s,...);
void debugf(const char*fmt,...);

struct lexeme{
  const char*val;
  unsigned len;
};

struct ast{
  int type,node_cnt;
  const char* value;
  struct ast* childen[];
};
typedef void (*eval_fn)(struct ast*,int);
// struct ast* newbase(int type,int cnt,const char*val,...);
struct ast* newast(int type,int cnt,const char*val,...);
struct ast* newterm(int type, const char* val);
// struct ast* newterm(int type, struct lexeme* val);

void eval(struct ast*,eval_fn);
void astfree(struct ast*);