%option noyywrap nodefault yylineno
%x COMMENT
%{
#include<stdio.h>
#include<string.h>
#include"minus.tab.h"
#include"minus.h"
int column = 1;
int cline,ccol;
#define debug 1
void printToken(const char*,const char*,int,int);
%}

id [a-zA-Z]+
num [0-9]+
relop ([<>]=?)|([=!]=)
addop [+-]
mulop [*/]

%%

if      {printToken("keyword",yytext,yylineno,column);column+=2;yylval.id=yytext;return IF;}
else    {printToken("keyword",yytext,yylineno,column);column+=4;yylval.id=yytext;return ELSE;}
return  {printToken("keyword",yytext,yylineno,column);column+=6;yylval.id=yytext;return RETURN;}
void    {printToken("keyword",yytext,yylineno,column);column+=4;yylval.id=yytext;return VOID;}
int     {printToken("keyword",yytext,yylineno,column);column+=3;yylval.id=yytext;return INT;}
while   {printToken("keyword",yytext,yylineno,column);column+=5;yylval.id=yytext;return WHILE;}

{addop} {printToken("op",yytext,yylineno,column);++column;              yylval.id=yytext;return addop;}
{mulop} {printToken("op",yytext,yylineno,column);++column;              yylval.id=yytext;return mulop;}
{relop} {printToken("op",yytext,yylineno,column);column+=strlen(yytext);yylval.id=yytext;return relop;}

"{" {printToken("braket",yytext,yylineno,column);     ++column;yylval.id=yytext;return LL;}
"}" {printToken("braket",yytext,yylineno,column);     ++column;yylval.id=yytext;return RL;}
"[" {printToken("braket",yytext,yylineno,column);     ++column;yylval.id=yytext;return LM;}
"]" {printToken("braket",yytext,yylineno,column);     ++column;yylval.id=yytext;return RM;}
"(" {printToken("braket",yytext,yylineno,column);     ++column;yylval.id=yytext;return LS;}
")" {printToken("braket",yytext,yylineno,column);     ++column;yylval.id=yytext;return RS;}

";" {printToken("SemiComma",yytext,yylineno,column);  ++column;yylval.id=yytext;return SEMI;}
"=" {printToken("Assign",yytext,yylineno,column);     ++column;yylval.id=yytext;return ASS;}
"," {printToken("Comma",yytext,yylineno,column);      ++column;yylval.id=yytext;return COMMA;}
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
  fprintf(stderr,"(%d,%d)unterminated comment start here\n",cline,ccol);
  return 0;
}

{id}  {printToken("id",yytext,yylineno,column); column+=strlen(yytext);yylval.id=yytext;return ID;}
{num} {printToken("num",yytext,yylineno,column);column+=strlen(yytext);yylval.id=yytext;return NUM;}
\n {column = 1;}
. {++column;}
%%

void printToken(const char*type,const char*val,int row,int col){
  if(debug){
    printf("%s:<%s> (%d,%d)\n",type,val,row,col);
  }
}