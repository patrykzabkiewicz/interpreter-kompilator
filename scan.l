%{
#include <stdlib.h>
#include "includes.h"
#include "y.tab.h"
%}

%%

[a-z]			{
				yylval.sIndex= yytext[0] - 'a';

				return VARIABLE;
			}

[0-9]+			{
				yylval.iValue= atoi( yytext );

				return INTEGER;
			}

[-!()<>=+*^/;{}.]	{
				return yytext[0];
			}

">="			{ return GE; }
"<="			{ return LE; }
"=="			{ return EQ; }
"!="			{ return NE; }
"while"			{ return WHILE; }
"if"			{ return IF; }
"else"			{ return ELSE; }
"print"			{ return PRINT; }

[ \t\n]			{ ; }
.			{ yyerror( "bledny znak" ); }

%%
