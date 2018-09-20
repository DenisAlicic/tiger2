/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_TAB_HPP_INCLUDED
# define YY_YY_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    VAR_T = 258,
    TYPE_T = 259,
    FUNC_T = 260,
    LET_T = 261,
    IN_T = 262,
    END_T = 263,
    IF_T = 264,
    ELSE_T = 265,
    THEN_T = 266,
    WHILE_T = 267,
    FOR_T = 268,
    DO_T = 269,
    BREAK_T = 270,
    NIL_T = 271,
    ARRAY_T = 272,
    DOT_T = 273,
    AND_T = 274,
    OR_T = 275,
    EQ_T = 276,
    GT_T = 277,
    GE_T = 278,
    LT_T = 279,
    LE_T = 280,
    NEQ_T = 281,
    DIV_T = 282,
    OF_T = 283,
    ASSIGN_T = 284,
    PLUS_T = 285,
    MINUS_T = 286,
    TIMES_T = 287,
    TO_T = 288,
    COLON_T = 289,
    NUM_T = 290,
    ID_T = 291,
    STRING_T = 292
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 53 "parser.ypp" /* yacc.c:1909  */

  int d;
  std::string* s;
  absyn::Absyn* synTree;
  absyn::ExpList* expList;
  absyn::DecList* decList;

#line 100 "parser.tab.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_HPP_INCLUDED  */
