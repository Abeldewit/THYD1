/* SC-T-603-THYD Fall 2019. Project, lexical analysis. */
%option c++
%option noyywrap
%option yylineno
%option caseless
%{
#include "language.h"
#include "common.h"
#include "lexer.h"

%}
ws [ \t\r\n]
digit [0-9]
alpha [a-zA-Z]
%x STAR_COMMENT
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


[a-zA-Z_][a-zA-Z0-9_]*  { auto it = LNG::ReservedWordToTokenName.find( Common::to_lower( yytext ) );
                          if ( it != LNG::ReservedWordToTokenName.end() ) {
                              return it->second;
                        } else {
                              return LNG::TokenName::t_identifier;
                        }}




"'".*"'"                { return LNG::TokenName::t_string_l; }

"'"[^']*$               { throw Lexer::LexerException(Common::Location{0, 0}, yytext ); }

{digit}+("."{digit}+)(("e"|"E")("-"|"+")?{digit}+)?	{ return LNG::TokenName::t_real; }
{digit}+("."{digit}+)?(("e"|"E")("-"|"+")?{digit}+)	{ return LNG::TokenName::t_real; }
{digit}+				{ return LNG::TokenName::t_integer; }
"{"(?:[^\}])*"}"		/*  {} style of a comment */
"{"[^\}]*               { throw Lexer::LexerException(Common::Location{0, 0}, "non-ending {} comment!" ); }

"(*"                    { BEGIN(STAR_COMMENT); }
<STAR_COMMENT>"*)"      { BEGIN(INITIAL); }
<STAR_COMMENT>.         { }
<STAR_COMMENT>\n        { }
<STAR_COMMENT><<EOF>>   { throw Lexer::LexerException(Common::Location{0, 0}, "non-ending (**) comment!" ); }

.               		{ return LNG::TokenName::t_unknown; }

%%
 // No need to add any code here.
