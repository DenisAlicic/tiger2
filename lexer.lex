%option noyywrap
%option nounput
%option noinput

%{
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include "absyn.hpp"
#include "symbol.hpp"
#include "frame.hpp"
#include "mips.hpp"
#include "semant.hpp"
#include "translate.hpp"
#include "tree.hpp"
#include "errormsg.hpp"
#include "canon.hpp"
#include "parser.tab.hpp"

/* This function updates position  * 
 * ex: @$.first_line, @1.last_line */ 
/* static void update_loc() */
/* { */
/* 	static int curr_line = 1; */
/* 	static int curr_col  = 1; */

/* 	yylloc.first_line   = curr_line; */
/* 	yylloc.first_column = curr_col; */

/* 	{ */
/* 		char * s; */ 
/* 		for(s = yytext; *s != '\0'; s++) { */
/* 			if (*s == '\n') { */
/* 				curr_line++; */
/* 				curr_col = 1; */
/* 			} else { */
/* 				curr_col++; */
/* 			} */
/* 		} */
/* 	} */
/* 	yyalloc.last_line   = curr_line; */
/* 	yyalloc.last_column = curr_col-1; */
/* } */
/* #define YY_USER_ACTION update_loc(); */
%}

%%
"var" return VAR_T;
"type" return TYPE_T;
"function" return FUNC_T;
"let" return LET_T;
"in" return IN_T;
"end" return END_T;
"if" return IF_T;
"then" return THEN_T;
"else" return ELSE_T;
"while" return WHILE_T;
"for" return FOR_T;
"do" return DO_T;
"to" return TO_T;
"break" return BREAK_T;
"nil" return NIL_T;
"array" return ARRAY_T;
"of" return OF_T;
":" return COLON_T;
"&" return AND_T;
"|" return OR_T;
"=" return EQ_T;
":=" return  ASSIGN_T;
"!=" return NEQ_T;
"<" return LT_T;
"<=" return LE_T;
">" return GT_T;
">=" return GE_T;
"." return DOT_T;
"/" return DIV_T;
"+" return PLUS_T;
"-" return MINUS_T;
"*" return TIMES_T;

[""<>,;{}+*&[\]()|=-] return *yytext;

[0-9]+ {
	yylval.d = atoi(yytext);
	return NUM_T;
}

[A-Za-z_][A-Za-z_0-9]* {
	yylval.s = new std::string(yytext);
	return ID_T;
}

\"[\\ A-Za-z_0-9.]*\" {
	yylval.s = new std::string(yytext);
	return STRING_T;
}

[ \s\t\n] {}

. {
	std::cerr << "Unknown symbol: " << yytext << std::endl;
	exit(EXIT_FAILURE);
}
%%
