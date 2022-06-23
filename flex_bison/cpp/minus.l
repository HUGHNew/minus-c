%option noyywrap nodefault
%x COMMENT
%{
#include <cstdlib>

#include "minus.cpp.hh"
#include "minus.tab.hh"

#define YY_DECL int yylex(yy::minuspp::semantic_type *yylval, \
    yy::minuspp::location_type *yylloc)

// make location include the current token
# define YY_USER_ACTION  yylloc->columns (yyleng);

typedef yy::minuspp::token token;

#define debug 0
void printToken(const char*,const char*);
%}

id [a-zA-Z]+
num [0-9]+
relop ([<>]=?)|([=!]=)
addop [+-]
mulop [*/]

%%
%{
  // start where previous token ended
  yylloc->step ();
%}

if      {printToken("keyword",yytext);yylloc->step();yylval.id=newlex(yytext);return token::IF;}
else    {printToken("keyword",yytext);yylloc->step();yylval.id=newlex(yytext);return token::ELSE;}
return  {printToken("keyword",yytext);yylloc->step();yylval.id=newlex(yytext);return token::RETURN;}
void    {printToken("keyword",yytext);yylloc->step();yylval.id=newlex(yytext);return token::VOID;}
int     {printToken("keyword",yytext);yylloc->step();yylval.id=newlex(yytext);return token::INT;}
while   {printToken("keyword",yytext);yylloc->step();yylval.id=newlex(yytext);return token::WHILE;}

{addop} {printToken("op",yytext);yylloc->step();  yylval.id=newlex(yytext);return token::addop;}
{mulop} {printToken("op",yytext);yylloc->step();  yylval.id=newlex(yytext);return token::mulop;}
{relop} {printToken("op",yytext);yylloc->step();  yylval.id=newlex(yytext);return token::relop;}

"{" {printToken("braket",yytext);     yylloc->step();yylval.id=newlex(yytext);return token::LL;}
"}" {printToken("braket",yytext);     yylloc->step();yylval.id=newlex(yytext);return token::RL;}
"[" {printToken("braket",yytext);     yylloc->step();yylval.id=newlex(yytext);return token::LM;}
"]" {printToken("braket",yytext);     yylloc->step();yylval.id=newlex(yytext);return token::RM;}
"(" {printToken("braket",yytext);     yylloc->step();yylval.id=newlex(yytext);return token::LS;}
")" {printToken("braket",yytext);     yylloc->step();yylval.id=newlex(yytext);return token::RS;}

";" {printToken("SemiComma",yytext);  yylloc->step();yylval.id=newlex(yytext);return token::SEMI;}
"=" {printToken("Assign",yytext);     yylloc->step();yylval.id=newlex(yytext);return token::ASS;}
"," {printToken("Comma",yytext);      yylloc->step();yylval.id=newlex(yytext);return token::COMMA;}
"/*"  {
  yylloc->step();
  BEGIN(COMMENT);
}
<COMMENT>"*/"     {yylloc->step();}
<COMMENT>[^*\n]+  {yylloc->step();}
<COMMENT>\n+      {yylloc->lines(1);}
<COMMENT>.        {yylloc->step();}
<COMMENT><<EOF>> {
  fprintf(stderr,"unterminated comment detected");
  BEGIN(INITIAL);
  return 0;
}

{id}  {printToken("id",yytext); yylloc->step();yylval.id=newlex(yytext);return token::ID;}
{num} {printToken("num",yytext);yylloc->step();yylval.id=newlex(yytext);return token::NUM;}
\n {yylloc->lines(1);}
. {yylloc->step();}
%%

void printToken(const char*type,const char*val){
  if(debug){
    printf("%s:<%s>\n",type,val);
  }
}