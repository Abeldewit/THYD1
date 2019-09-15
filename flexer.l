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

"absolute"				{ return LNG::TokenName::t_absolute; }
"and"				    { return LNG::TokenName::t_and; }
"array"				    { return LNG::TokenName::t_array; }
"begin"			    	{ return LNG::TokenName::t_begin; }
"boolean"				{ return LNG::TokenName::t_boolean; }
"byte"			    	{ return LNG::TokenName::t_byte; }
"case"			    	{ return LNG::TokenName::t_case; }
"char"			    	{ return LNG::TokenName::t_char; }
"const"			    	{ return LNG::TokenName::t_const; }
"div"				    { return LNG::TokenName::t_div; }
"do"			    	{ return LNG::TokenName::t_do; }
"downto"				{ return LNG::TokenName::t_downto; }
"else"				    { return LNG::TokenName::t_else; }
"end"				    { return LNG::TokenName::t_end; }
"external"				{ return LNG::TokenName::t_external; }
"false"				    { return LNG::TokenName::t_false; }
"file"				    { return LNG::TokenName::t_file; }
"forward"				{ return LNG::TokenName::t_forward; }
"for"				    { return LNG::TokenName::t_for; }
"function"				{ return LNG::TokenName::t_function; }
"goto"				    { return LNG::TokenName::t_goto; }
"if"				    { return LNG::TokenName::t_if; }
"in"				    { return LNG::TokenName::t_in; }
"integer"				{ return LNG::TokenName::t_integer; }
"inline"				{ return LNG::TokenName::t_inline; }
"label"				    { return LNG::TokenName::t_label; }
"mod"				    { return LNG::TokenName::t_mod; }
"nil"				    { return LNG::TokenName::t_nil; }
"not"				    { return LNG::TokenName::t_not; }
"of"				    { return LNG::TokenName::t_of; }
"or"			    	{ return LNG::TokenName::t_or; }
"overlay"				{ return LNG::TokenName::t_overlay; }
"packed"				{ return LNG::TokenName::t_packed; }
"procedure"				{ return LNG::TokenName::t_procedure; }
"program"				{ return LNG::TokenName::t_program; }
"real"				    { return LNG::TokenName::t_real; }
"record"				{ return LNG::TokenName::t_record; }
"repeat"				{ return LNG::TokenName::t_repeat; }
"set"				    { return LNG::TokenName::t_set; }
"shl"				    { return LNG::TokenName::t_shl; }
"shr"   				{ return LNG::TokenName::t_shr; }
"string"				{ return LNG::TokenName::t_string; }
"then"	    			{ return LNG::TokenName::t_then; }
"to"		    		{ return LNG::TokenName::t_to; }
"true"			    	{ return LNG::TokenName::t_true; }
"name"				    { return LNG::TokenName::t_type; }
"until"				    { return LNG::TokenName::t_until; }
"var"				    { return LNG::TokenName::t_var; }
"while"				    { return LNG::TokenName::t_while; }
"with"				    { return LNG::TokenName::t_with; }
"xor"				    { return LNG::TokenName::t_xor; }

[a-zA-Z_][a-zA-Z0-9_]*  { return LNG::TokenName::t_identifier; }
"{"(?:[^\}])*"}"		/* comment */

.               		{ return LNG::TokenName::t_unknown; }

%%
 // No need to add any code here.
