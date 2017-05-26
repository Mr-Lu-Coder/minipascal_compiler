%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "pascal_yacc.h"
#include "table.h"

%}   
/************************************
*	MACRO DEFINITION	*
*************************************/
letter		[A-Za-z]
alnum			[A-Za-z0-9]
d					[0-9]
white			[\t\n\040]
%start		COMMENT

/*****************************************
*	RECOGNIION RULES	         *
*****************************************/
%%

\{														{ECHO;BEGIN COMMENT;}
<COMMENT>\}										{ECHO;BEGIN 0;}
<COMMENT>\n										{ECHO;}
<COMMENT>[^}]+ 								{ECHO;}
[Bb][eE][Gg][iI][Nn]					{ECHO;return Begin;}
[eE][Nn][Dd]									{ECHO;return End;}
[Pp][Rr][oO][Gg][Rr][Aa][Mm]	{ECHO;return Program;}
[Vv][Aa][Rr]									{ECHO;return Var;}
[Ii][nN][Tt][eE][Gg][eE][Rr]	{ECHO;return Integer;}
[Rr][eE][Aa][lL]							{ECHO;return Real;}
[Ww][Hh][Ii][Ll][Ee]					{ECHO;return While;}
[Dd][oO]					{ECHO;return Do;}
[iI][Ff]					{ECHO;return If;}
[Tt][Hh][Ee][Nn]	{ECHO;return Then;}
[Ee][Ll][Ss][Ee]	{ECHO;return Else;}
[Aa][Nn][Dd]			{ECHO;return And;}
[Oo][Rr]					{ECHO;return Or;}
[Nn][Oo][Tt]			{ECHO;return Not;}
[Ff][Oo][Rr]			{ECHO;return For;}
[Tt][Oo]			{ECHO;return To;}

({d}+(\.{d}*)?[Ee]([+-])?{d}+)|({d}*\.{d}+[Ee]([+-])?{d}+)	{ECHO;strcpy(yylval.str,yytext);return RealNo;}
{d}+\.{d}*|{d}*\.{d}+		{ECHO;strcpy(yylval.str,yytext);return RealNo;}
{d}+										{ECHO;strcpy(yylval.str,yytext);return IntNo;}

"("			{ECHO;return '(';}
")"			{ECHO;return ')';}
"["			{ECHO;return '[';}
"]"			{ECHO;return ']';}
">"			{ECHO;return '>';}
"<"			{ECHO;return '<';}
"="			{ECHO;return '=';}
"<="		{ECHO;return LE;}
">="		{ECHO;return GE;}
"<>"		{ECHO;return NE;}
":"			{ECHO;return ':';}
";"			{ECHO;return ';';}
"\."		{ECHO;return '.';}
"*"			{ECHO;return '*';}
"+"			{ECHO;return '+';}
"-"			{ECHO;return '-';}
"/"			{ECHO;return '/';}
"%"			{ECHO;return '%';}
","			{ECHO;return ',';}
{letter}{alnum}*	{ ECHO;strcpy(yylval.str,yytext); return Iden;}
{white}+		{ECHO;}
.						{printf("Invalid char %s\n",yytext);return ERRORCHAR; }

%%

#ifndef yywrap
int yywrap()
{
	return 1;
}
#endif
