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
":="		            { return LNG::TokenName::t_assign; }
"="		                { return LNG::TokenName::t_eq; }
"/"		                { return LNG::TokenName::t_divide; }
">"		                { return LNG::TokenName::t_gt; }
">="		            { return LNG::TokenName::t_gteq; }
"<"		                { return LNG::TokenName::t_lt; }
"<="		            { return LNG::TokenName::t_lteq; }
"-"		                { return LNG::TokenName::t_minus; }
"*"		                { return LNG::TokenName::t_multiply; }
"<>"		            { return LNG::TokenName::t_neq; }
"+"		                { return LNG::TokenName::t_plus; }
"^"		                { return LNG::TokenName::t_caret; }
":"		                { return LNG::TokenName::t_colon; }
","		                { return LNG::TokenName::t_comma; }
"."		                { return LNG::TokenName::t_dot; }
"["		                { return LNG::TokenName::t_lbracket; }
"("		                { return LNG::TokenName::t_lparenthesis; }
"]"		                { return LNG::TokenName::t_rbracket; }
")"		                { return LNG::TokenName::t_rparenthesis; }
".."		            { return LNG::TokenName::t_subrange; }
";"		                { return LNG::TokenName::t_semicolon; }
"{"(?:[^\}])*"}"		/* comment */

.               		{ return LNG::TokenName::t_unknown; }

%%
 // No need to add any code here.
