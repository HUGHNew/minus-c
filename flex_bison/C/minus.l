%option noyywrap nodefault yylineno
%x COMMENT
%{
#include<stdio.h>
#include<string.h>
#include"y.tab.h"
#include"minus.h"
int column = 1;
int cline,ccol;
#define debug 0
void printToken(const char*,const char*,int,int);
%}

id [a-zA-Z]+
num [0-9]+
relop ([<>]=?)|([=!]=)
addop [+-]
mulop [*/]

%%

if      {printToken("keyword",yytext,yylineno,column);column+=2;yylval.id=newlex(yytext);return IF;}
else    {printToken("keyword",yytext,yylineno,column);column+=4;yylval.id=newlex(yytext);return ELSE;}
return  {printToken("keyword",yytext,yylineno,column);column+=6;yylval.id=newlex(yytext);return RETURN;}
void    {printToken("keyword",yytext,yylineno,column);column+=4;yylval.id=newlex(yytext);return VOID;}
int     {printToken("keyword",yytext,yylineno,column);column+=3;yylval.id=newlex(yytext);return INT;}
while   {printToken("keyword",yytext,yylineno,column);column+=5;yylval.id=newlex(yytext);return WHILE;}

{addop} {printToken("op",yytext,yylineno,column);++column;              yylval.id=newlex(yytext);return addop;}
{mulop} {printToken("op",yytext,yylineno,column);++column;              yylval.id=newlex(yytext);return mulop;}
{relop} {printToken("op",yytext,yylineno,column);column+=strlen(yytext);yylval.id=newlex(yytext);return relop;}

"{" {printToken("braket",yytext,yylineno,column);     ++column;yylval.id=newlex(yytext);return LL;}
"}" {printToken("braket",yytext,yylineno,column);     ++column;yylval.id=newlex(yytext);return RL;}
"[" {printToken("braket",yytext,yylineno,column);     ++column;yylval.id=newlex(yytext);return LM;}
"]" {printToken("braket",yytext,yylineno,column);     ++column;yylval.id=newlex(yytext);return RM;}
"(" {printToken("braket",yytext,yylineno,column);     ++column;yylval.id=newlex(yytext);return LS;}
")" {printToken("braket",yytext,yylineno,column);     ++column;yylval.id=newlex(yytext);return RS;}

";" {printToken("SemiComma",yytext,yylineno,column);  ++column;yylval.id=newlex(yytext);return SEMI;}
"=" {printToken("Assign",yytext,yylineno,column);     ++column;yylval.id=newlex(yytext);return ASS;}
"," {printToken("Comma",yytext,yylineno,column);      ++column;yylval.id=newlex(yytext);return COMMA;}
"/*"  {
  cline = yylineno; ccol = column;
  column+=2;
  BEGIN(COMMENT);
}
<COMMENT>"*/" {column+=2;BEGIN(INITIAL);}
<COMMENT>[^*\n]+ {column+=strlen(yytext);}
<COMMENT>\n+ {column=1;}
<COMMENT>. {column+=1;}
<COMMENT><<EOF>> {
  yyerror("(%d,%d) unterminated comment start here",cline,ccol);
  return 0;
}

{id}  {printToken("id",yytext,yylineno,column); column+=strlen(yytext);yylval.id=newlex(yytext);return ID;}
{num} {printToken("num",yytext,yylineno,column);column+=strlen(yytext);yylval.id=newlex(yytext);return NUM;}
\n {column = 1;}
. {++column;}
%%

void printToken(const char*type,const char*val,int row,int col){
  if(debug){
    printf("%s:<%s> (%d,%d)\n",type,val,row,col);
  }
}