#include<stdio.h>
/* interface to the lexer */
extern int yylineno; /* from lexer */
extern FILE* yyin; /* from lexer */
extern int yylex(); /* from lexer */
extern int yyparse(); /* from parse */
void yyerror(char *s,...);
void debugf(const char*fmt,...);

struct lex{
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
#define LEX
struct lex* newlex(const char*);
// yylval.id->val=yytext;yylval.id->len=strlen(yytext);
// struct ast* newterm(int type, const char* val);
struct ast* newterm(int type, struct lex* val);
void show_ast(struct ast*,int);
void astfree(struct ast*);