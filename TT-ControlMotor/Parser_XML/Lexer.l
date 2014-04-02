%{

#include <stdlib.h>
enum yytokentype
  {
    VALUE = 258,
    OPEN = 259,
    CLOSE = 260,
    SLASH = 261,
    OPEN_HEADER = 263,
    CLOSE_HEADER = 264,
    QUOTE = 265,
    EQUAL = 266
  };
struct YYPOS{
	int line;
	int first_column;
	int last_column;
};

//Better error reporting
#define YY_USER_ACTION yylloc.line =  yylineno; \
    yylloc.first_column = yycolumn; yylloc.last_column = yycolumn + yyleng - 1; \
    yycolumn += yyleng; 

int yycolumn = 1;
extern char* yylval;
extern struct YYPOS yylloc;
%}
%option yylineno
%option noyywrap

%%

"<?xml"			{return OPEN_HEADER;}
"?>"			{return CLOSE_HEADER;}
"<"				{return OPEN;}
">"				{return CLOSE;}
"/"				{return SLASH;}
"\""			{return QUOTE;}
"="				{return EQUAL;}

[;0-9aA-zZ.-]+		{yylval = strdup(yytext); return VALUE; }

[ \t]*			{}
[\n]*			{yycolumn = 1; /* RESET della colonna ad ogni nuova riga */ }

%%	


