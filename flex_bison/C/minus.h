#include<stdio.h>
/* interface to the lexer */
extern int yylineno; /* from lexer */
extern FILE* yyin; /* from lexer */
extern int yylex(); /* from lexer */
extern int yyparse(); /* from parse */
void yyerror(char *s,...);
void debugf(const char*fmt,...);

struct lex{
  char*val;
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
#define LEX 1
#if LEX == 1
struct lex* newlex(const char*);
struct ast* newterm(int type, struct lex* val);
#else
struct ast* newterm(int type, const char* val);
#endif
void show_ast(struct ast*,int);
void astfree(struct ast*);