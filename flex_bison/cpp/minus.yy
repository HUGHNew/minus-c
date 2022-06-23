%language "C++"
%defines
%locations

%define parser_class_name "minuspp"
%define api.value.type variant

%{
#include "minus.cpp.h"
#include <iostream>
#include <numeric>
using namespace std;
#define PARSE_DEBUG 0
%}

%token<string> NUM
LL RL LM RM LS RS addop mulop
SEMI ASS COMMA
ID
IF ELSE RETURN VOID INT WHILE
relop

%type<pointer>program
decl_list decl var_decl type_spec func_decl
params params_list param param_suff compound_stmt
local_decls stmt_list stmt expr_stmt select_stmt else_stmt iter_stmt ret_stmt
expr var simple_expr add_expr term factor call args arg_list 
%%
program : decl_list {
    $$ = newast(NoT,1,"program -> decl_list",$1);
    show_ast($$);
    astfree($$);
  }
  ;
decl_list : decl{$$=newast(NoT,1,"decl_list -> decl",$1);}
  | decl decl_list{$$=newast(NoT,2,"decl_list-> decl decl_list",$1,$2);}
  ;

decl : var_decl {$$=newast(NoT,1,"decl -> var_decl ",$1);}
  | func_decl {$$=newast(NoT,1,"decl-> func_decl ",$1);}
  ;

var_decl : type_spec var SEMI{$$=newast(NoT,3,"var_decl -> type_spec var ;",$1,$2,newterm(Sign,$3));}
  ;

type_spec : INT {$$=newast(NoT,1,"type_spec -> int ",newterm(Sign,$1));}
  | VOID {$$=newast(NoT,1,"type_spec-> void ",newterm(Sign,$1));}
  ;

func_decl : type_spec ID LS params RS compound_stmt {$$=newast(NoT,6,"func_decl -> type_spec id ( params ) compound_stmt ",$1,newterm(Id,$2),newterm(Sign,$3),$4,newterm(Sign,$5),$6);}
  ;

params : params_list {$$=newast(NoT,1,"params -> params_list ",$1);}
  | VOID {$$=newast(NoT,1,"params-> void ",newterm(Sign,$1));}
  ;

params_list : param COMMA params_list{$$=newast(NoT,3,"params_list -> param , params_list",$1,newterm(Sign,$2),$3);}
  | param {$$=newast(NoT,1,"params_list-> param ",$1);}
  ;

param : type_spec param_suff {$$=newast(NoT,2,"param -> type_spec param_suff ",$1,$2);}
  ;

param_suff : ID {$$=newast(NoT,1,"param_suff -> id ",newterm(Id,$1));}
  | ID LM RM {$$=newast(NoT,3,"param_suff-> id [ ] ",newterm(Id,$1),newterm(Sign,$2),newterm(Sign,$3));}
  ;

compound_stmt : LL local_decls stmt_list RL{$$=newast(NoT,4,"compound_stmt -> { local_decls stmt_list }",newterm(Sign,$1),$2,$3,newterm(Sign,$4));}
  ;

local_decls :{$$=NULL;}| var_decl local_decls{$$=newast(NoT,2,"local_decls -> empty| var_decl local_decls",$1,$2);}
  ;

stmt_list :{$$=NULL;}| stmt stmt_list{$$=newast(NoT,2,"stmt_list -> empty| stmt stmt_list",$1,$2);}
  ;

stmt : expr_stmt{$$=newast(NoT,1,"stmt -> expr_stmt",$1);}
  | compound_stmt{$$=newast(NoT,1,"stmt-> compound_stmt",$1);}
  | select_stmt{$$=newast(NoT,1,"stmt-> select_stmt",$1);}
  | iter_stmt{$$=newast(NoT,1,"stmt-> iter_stmt",$1);}
  | ret_stmt{$$=newast(NoT,1,"stmt-> ret_stmt",$1);}
  ;

expr_stmt : expr SEMI{$$=newast(NoT,2,"expr_stmt -> expr ;",$1,newterm(Sign,$2));}
  | SEMI{$$=newast(NoT,1,"expr_stmt-> ;",newterm(Sign,$1));}
  ;

select_stmt : IF LS expr RS stmt else_stmt{$$=newast(NoT,6,"select_stmt -> if ( expr ) stmt else_stmt",newterm(Sign,$1),newterm(Sign,$2),$3,newterm(Sign,$4),$5,$6);}
  ;

else_stmt :{$$=NULL;}| ELSE stmt{$$=newast(NoT,3,"else_stmt -> empty| else stmt",newterm(Keyword,$1),$2);}
  ;

iter_stmt : WHILE LS expr RS stmt{$$=newast(NoT,5,"iter_stmt -> while ( expr ) stmt",newterm(Sign,$1),newterm(Sign,$2),$3,newterm(Sign,$4),$5);}
  ;

ret_stmt : RETURN expr_stmt{$$=newast(NoT,2,"ret_stmt -> return expr_stmt",newterm(Sign,$1),$2);}
  ;

expr : simple_expr{$$=newast(NoT,1,"expr -> simple_expr",$1);}
  |var ASS expr{$$=newast(NoT,3,"expr->var = expr",$1,newterm(Sign,$2),$3);}
  ;

var : ID {$$=newast(NoT,1,"var -> id ",newterm(Id,$1));}
  | ID LM expr RM{$$=newast(NoT,4,"var-> id [ expr ]",newterm(Id,$1),newterm(Sign,$2),$3,newterm(Sign,$4));}
  ;

simple_expr : add_expr{$$=newast(NoT,1,"simple_expr -> add_expr",$1);}
  |add_expr relop add_expr{$$=newast(NoT,3,"simple_expr->add_expr relop add_expr",$1,newterm(Op,$2),$3);}
  ;

add_expr : term{$$=newast(NoT,1,"add_expr -> term",$1);}
  |add_expr addop term{$$=newast(NoT,3,"add_expr->add_expr addop term",$1,newterm(Op,$2),$3);}
  ;

term : factor{$$=newast(NoT,1,"term -> factor",$1);}
  |term mulop factor{$$=newast(NoT,3,"term->term mulop factor",$1,newterm(Op,$2),$3);}
  ;

factor : NUM{$$=newast(NoT,1,"factor -> num",newterm(Sign,$1));}
  |LS expr RS{$$=newast(NoT,3,"factor->( expr )",newterm(Sign,$1),$2,newterm(Sign,$3));}
  |var{$$=newast(NoT,1,"factor->var",$1);}
  |call{$$=newast(NoT,1,"factor->call",$1);}
  ;

call : ID LS args RS {$$=newast(NoT,4,"call -> id ( args ) ",newterm(Id,$1),newterm(Sign,$2),$3,newterm(Sign,$4));}
  ;

args :{$$=NULL;}|arg_list{$$=newast(NoT,1,"args -> empty|arg_list",$1);}
  ;

arg_list : expr COMMA arg_list{$$=newast(NoT,3,"arg_list -> expr , arg_list",$1,newterm(Sign,$2),$3);}
  |expr{$$=newast(NoT,1,"arg_list->expr",$1);}
  ;
%%
namespace yy {
  void minuspp::error(location const &loc, const std::string& s){
    std::cerr << "error at " << loc << ": " << s << std::endl;
  }
}
void show_ast_helper(pointer const&root, int it)noexcept {
  if (root != nullptr) {
    int t_sum = accumulate(root->childen.begin(),root->childen.end(),0,[](int acc,auto&&it){
      return acc+it->childen.size();
    });
#ifdef PARSE_RULE
    Indent(stdout, it);
#endif
    if (root->type) {
#ifndef PARSE_RULE
      Indent(stdout, it - 1);
#endif
      printf("%s\n", root->value);
    } else {
#ifdef PARSE_RULE
      printf("<%s>\n", root->value);
#endif
      int n = t_sum == 0 ? it : it + 1;
      for (int i = 0; i < root->node_cnt; ++i) {
        show_ast_helper(root->childen[i], n);
      }
    }
  }
}
void show_ast(pointer const& p) noexcept{
  show_ast_helper(p,0);
}