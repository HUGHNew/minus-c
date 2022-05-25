%{
#include"minus.h"
void yyerror(char *s,...);
void show_ast(struct ast*,int);
enum TokenType{
  NoT,Id,Keyword,Num,Sign,Op
};
%}

%union{
  const char* id;
  struct ast* tree;
}

%token<id> NUM
%token<id> LL RL LM RM LS RS addop mulop
%token<id> SEMI ASS COMMA
%token<id> ID
%token<id> IF ELSE RETURN VOID INT WHILE
%token<id> relop

%type<tree>
decl_list decl var_decl type_spec func_decl
params params_list param param_suff compound_stmt
local_decls stmt_list stmt expr_stmt select_stmt else_stmt iter_stmt ret_stmt
expr var simple_expr add_expr term factor call args arg_list 
%%
