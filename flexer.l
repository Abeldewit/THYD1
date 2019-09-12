/* SC-T-603-THYD Fall 2019. Project, lexical analysis. */
%option c++
%option noyywrap
%option yylineno
%{
#include "language.h"
%}
ws [ \t\r\n]
digit [0-9]
alpha [a-zA-Z]

%%

{ws}+             		/* do nothing */
"["             		{ return LNG::TokenName::t_lbracket; }
"]"             		{ return LNG::TokenName::t_rbracket; }
"{"(?:[^\}])*"}"		/* comment */

.               		{ return LNG::TokenName::t_unknown; }

%%
 // No need to add any code here.
