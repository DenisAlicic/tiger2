/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.ypp" /* yacc.c:339  */

#include <iostream>
#include <string>
#include <cstdlib>
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
#define YYDEBUG 1

int yylex();

void yyerror(std::string s) {
  std::cerr << s << std::endl;
  exit(EXIT_FAILURE);
}

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

void prStmList(tree::Print* print, tree::StmList* stms) {
	for (tree::StmList* l = stms; l != nullptr; l = l->m_tail){
		print->prStm(l->m_head);
	}
}


void emitProc(std::ostream& out, frag::ProcFrag* f) {
	tree::Print* print = new tree::Print(out);

	tree::Stm* x = f->m_body;
	//print->prStm(x); //ok

//	tree::StmList* stms = canon::Canon::linearize(f->m_body);
//	prStmList(print, stms); //ok
//	canon::BasicBlocks* b = new canon::BasicBlocks(stms);
//	tree::StmList* traced = (new canon::TraceSchedule(b))->m_stms;
//	prStmList(print, traced); //ok
}



#line 117 "parser.tab.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.hpp".  */
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
#line 53 "parser.ypp" /* yacc.c:355  */

  int d;
  std::string* s;
  absyn::Absyn* synTree;
  absyn::ExpList* expList;
  absyn::DecList* decList;

#line 203 "parser.tab.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 220 "parser.tab.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  35
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   366

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  16
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  147

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      38,    40,     2,     2,    44,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    45,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    39,     2,    43,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,    42,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    84,    84,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   154,   155,   156,   157,   160,
     161,   164,   165,   168,   169,   172,   173,   176,   177,   178,
     181,   182,   185,   188,   189,   190,   191,   194,   195,   199,
     200,   203,   204,   207,   208,   209,   210
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VAR_T", "TYPE_T", "FUNC_T", "LET_T",
  "IN_T", "END_T", "IF_T", "ELSE_T", "THEN_T", "WHILE_T", "FOR_T", "DO_T",
  "BREAK_T", "NIL_T", "ARRAY_T", "DOT_T", "AND_T", "OR_T", "EQ_T", "GT_T",
  "GE_T", "LT_T", "LE_T", "NEQ_T", "DIV_T", "OF_T", "ASSIGN_T", "PLUS_T",
  "MINUS_T", "TIMES_T", "TO_T", "COLON_T", "NUM_T", "ID_T", "STRING_T",
  "'('", "'['", "')'", "'{'", "'}'", "']'", "','", "';'", "$accept",
  "program", "expr", "lvalue", "exprlist", "exprseq", "fieldlist",
  "declarationlist", "declaration", "typedeclist", "typedeclaration",
  "type", "typefields", "variabledeclaration", "functiondeclist",
  "functiondeclaration", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,    40,    91,
      41,   123,   125,    93,    44,    59
};
# endif

#define YYPACT_NINF -105

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-105)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-1)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     144,    21,   144,   144,   -30,  -105,  -105,   144,  -105,    90,
    -105,    55,     8,   296,    33,    -4,    19,    20,    56,    21,
    -105,    62,  -105,  -105,    70,   239,   253,    48,    42,    67,
     144,    -9,  -105,   -10,    38,  -105,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,    45,   144,
     144,    72,    63,    49,   111,  -105,  -105,  -105,   144,   144,
     144,  -105,   142,    59,   183,    68,  -105,    46,   144,  -105,
     322,   310,   334,   334,   334,   334,   334,   334,  -105,    42,
      42,  -105,  -105,   296,   197,   144,    60,   -13,    17,  -105,
      92,   222,   296,   281,   144,  -105,    80,   144,  -105,  -105,
    -105,   296,    81,    85,  -105,    12,  -105,    75,    -3,    78,
    -105,   144,   144,  -105,   144,   168,   144,    79,  -105,    83,
      86,   144,    94,    31,   296,   267,   296,    96,   296,  -105,
    -105,    89,   296,   114,   144,   101,   144,  -105,   102,   144,
     296,   119,   296,  -105,   296,   144,   296
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,    32,     6,     0,     4,    37,
       5,     0,     0,     2,     7,     0,     0,     0,     0,    45,
      47,    50,    48,    49,    61,     0,     0,     0,     3,     0,
       0,     0,    24,    41,     0,     1,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    46,    51,    62,     0,     0,
       0,    22,    39,     0,     0,     0,    26,     0,     0,    23,
      13,    12,    14,    17,    18,    15,    16,    19,     9,    10,
      11,     8,    36,    20,     0,     0,     0,     0,     0,    33,
       0,    28,    30,     0,     0,    21,    38,     0,    25,    42,
      35,    59,     0,     0,    53,     0,    52,     0,     0,     0,
      34,     0,     0,    40,     0,    43,     0,     0,    55,     0,
       0,     0,     0,     0,    29,     0,    27,     0,    60,    56,
      54,    57,    63,     0,     0,     0,     0,    44,     0,     0,
      64,     0,    31,    58,    65,     0,    66
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -105,  -105,     0,  -105,    47,   -49,    16,   125,  -105,   130,
    -105,  -105,  -104,  -105,   128,  -105
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    12,    33,    14,    63,    34,    67,    18,    19,    20,
      21,   106,   109,    22,    23,    24
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      13,   119,    25,    26,   103,    90,    27,    28,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,   121,    99,
      45,    46,    47,   104,    15,    16,    17,    65,   105,    62,
      64,   122,    51,    66,   143,    68,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,   107,    83,
      84,    48,   134,   107,   118,    52,    53,   108,    91,    92,
      93,     1,    49,    54,     2,   135,    16,     3,     4,    44,
       5,     6,    50,     1,    47,    17,     2,    60,    69,     3,
       4,    82,     5,     6,    87,   101,     7,    88,    98,    97,
       8,     9,    10,    11,    62,    32,   102,   115,     7,    95,
     110,    85,     8,     9,    10,    11,    86,    61,   114,   120,
     116,   124,   125,   117,   126,   129,   128,     1,   123,    89,
       2,   132,   131,     3,     4,   130,     5,     6,    29,    30,
     133,    31,    65,   138,   140,   139,   142,   141,   107,   144,
     145,   113,     7,   137,    55,   146,     8,     9,    10,    11,
       1,    56,    57,     2,     0,     0,     3,     4,     0,     5,
       6,    36,    37,    38,    39,    40,    41,    42,    43,    44,
       0,     0,    45,    46,    47,     7,     0,     0,     0,     8,
       9,    10,    11,     0,     0,     0,    94,    36,    37,    38,
      39,    40,    41,    42,    43,    44,     0,     0,    45,    46,
      47,     0,    36,    37,    38,    39,    40,    41,    42,    43,
      44,     0,   127,    45,    46,    47,    36,    37,    38,    39,
      40,    41,    42,    43,    44,     0,    96,    45,    46,    47,
       0,     0,   111,     0,     0,     0,     0,     0,     0,     0,
     100,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      58,     0,    45,    46,    47,     0,     0,     0,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    59,     0,    45,
      46,    47,    36,    37,    38,    39,    40,    41,    42,    43,
      44,   136,     0,    45,    46,    47,    36,    37,    38,    39,
      40,    41,    42,    43,    44,     0,     0,    45,    46,    47,
      36,    37,    38,    39,    40,    41,    42,    43,    44,     0,
       0,    45,    46,    47,   112,    36,    37,    38,    39,    40,
      41,    42,    43,    44,     0,     0,    45,    46,    47,    36,
       0,    38,    39,    40,    41,    42,    43,    44,     0,     0,
      45,    46,    47,    38,    39,    40,    41,    42,    43,    44,
       0,     0,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    44,     0,     0,    45,    46,    47
};

static const yytype_int16 yycheck[] =
{
       0,   105,     2,     3,    17,    54,    36,     7,     0,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    21,    68,
      30,    31,    32,    36,     3,     4,     5,    36,    41,    29,
      30,    34,    36,    42,   138,    45,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    36,    49,
      50,    18,    21,    36,    42,    36,    36,    40,    58,    59,
      60,     6,    29,     7,     9,    34,     4,    12,    13,    27,
      15,    16,    39,     6,    32,     5,     9,    29,    40,    12,
      13,    36,    15,    16,    21,    85,    31,    38,    42,    21,
      35,    36,    37,    38,    94,    40,    36,    97,    31,    40,
       8,    29,    35,    36,    37,    38,    34,    40,    28,    34,
      29,   111,   112,    28,   114,    36,   116,     6,    40,     8,
       9,   121,    36,    12,    13,    42,    15,    16,    38,    39,
      36,    41,    36,    44,   134,    21,   136,    36,    36,   139,
      21,    94,    31,   127,    19,   145,    35,    36,    37,    38,
       6,    21,    24,     9,    -1,    -1,    12,    13,    -1,    15,
      16,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      -1,    -1,    30,    31,    32,    31,    -1,    -1,    -1,    35,
      36,    37,    38,    -1,    -1,    -1,    44,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    -1,    -1,    30,    31,
      32,    -1,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    -1,    44,    30,    31,    32,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    -1,    43,    30,    31,    32,
      -1,    -1,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      11,    -1,    30,    31,    32,    -1,    -1,    -1,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    14,    -1,    30,
      31,    32,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    14,    -1,    30,    31,    32,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    19,
      -1,    21,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    21,    22,    23,    24,    25,    26,    27,
      -1,    -1,    30,    31,    32,    21,    22,    23,    24,    25,
      26,    27,    -1,    -1,    30,    31,    32
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     9,    12,    13,    15,    16,    31,    35,    36,
      37,    38,    47,    48,    49,     3,     4,     5,    53,    54,
      55,    56,    59,    60,    61,    48,    48,    36,    48,    38,
      39,    41,    40,    48,    51,     0,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    30,    31,    32,    18,    29,
      39,    36,    36,    36,     7,    53,    55,    60,    11,    14,
      29,    40,    48,    50,    48,    36,    42,    52,    45,    40,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    36,    48,    48,    29,    34,    21,    38,     8,
      51,    48,    48,    48,    44,    40,    43,    21,    42,    51,
      43,    48,    36,    17,    36,    41,    57,    36,    40,    58,
       8,    10,    33,    50,    28,    48,    29,    28,    42,    58,
      34,    21,    34,    40,    48,    48,    48,    44,    48,    36,
      42,    36,    48,    36,    21,    34,    14,    52,    44,    21,
      48,    36,    48,    58,    48,    21,    48
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    49,    49,    49,    49,    50,
      50,    51,    51,    52,    52,    53,    53,    54,    54,    54,
      55,    55,    56,    57,    57,    57,    57,    58,    58,    59,
      59,    60,    60,    61,    61,    61,    61
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     4,     3,     3,     2,     4,     3,     6,     4,     6,
       4,     8,     1,     4,     5,     4,     3,     1,     4,     1,
       3,     1,     3,     3,     5,     1,     2,     1,     1,     1,
       1,     2,     4,     1,     3,     2,     3,     3,     5,     4,
       6,     1,     2,     6,     7,     8,     9
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 84 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = (yyvsp[0].synTree);

	    std::string filename = "tests/test.tig";
	    tiger::errormsg::ErrorMsg* errorMsg = new tiger::errormsg::ErrorMsg(filename);

	    absyn::Print pr(std::cout);
	    pr.prExp((absyn::Exp*)(yyval.synTree), 0);
	    std::cout << std::endl;

		frame::Frame* frame = new mips::MipsFrame();
		translate::Translate* translator = new translate::Translate(frame);
		semant::Semant* smt = new semant::Semant(translator, errorMsg);
		frag::Frag* frags = smt->transProg((absyn::Exp*)(yyval.synTree));


		if (tiger::errormsg::ErrorMsg::anyErrors == false) {

				std::cout << ".globl main" << std::endl;

			for (frag::Frag* f = frags; f != nullptr; f = f->m_next){
				if (instanceof<frag::ProcFrag>(f))
				{
					emitProc(std::cout, (frag::ProcFrag*)f);
				}
				else if (instanceof<frag::DataFrag>(f)) {
					std::cout << ("\n.data\n" + ((frag::DataFrag*)f)->m_data);
				}
			}
	   }

       delete (yyval.synTree);
}
#line 1466 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 118 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::OpExp(0, new absyn::IntExp((yyvsp[0].synTree)->m_pos,0), absyn::OpExp::MINUS, (absyn::Exp*)(yyvsp[0].synTree)); }
#line 1472 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 119 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::IntExp(0, (yyvsp[0].d)); }
#line 1478 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 120 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::StringExp(0, *(yyvsp[0].s)); delete (yyvsp[0].s); }
#line 1484 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 121 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::NilExp(0); }
#line 1490 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 122 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::VarExp((yyvsp[0].synTree)->m_pos, (absyn::Var*)(yyvsp[0].synTree)); }
#line 1496 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 123 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::OpExp((yyvsp[-2].synTree)->m_pos, (absyn::Exp*)(yyvsp[-2].synTree), absyn::OpExp::MUL, (absyn::Exp*)(yyvsp[0].synTree)); }
#line 1502 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 124 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::OpExp((yyvsp[-2].synTree)->m_pos, (absyn::Exp*)(yyvsp[-2].synTree), absyn::OpExp::DIV, (absyn::Exp*)(yyvsp[0].synTree)); }
#line 1508 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 125 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::OpExp((yyvsp[-2].synTree)->m_pos, (absyn::Exp*)(yyvsp[-2].synTree), absyn::OpExp::PLUS, (absyn::Exp*)(yyvsp[0].synTree)); }
#line 1514 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 126 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::OpExp((yyvsp[-2].synTree)->m_pos, (absyn::Exp*)(yyvsp[-2].synTree), absyn::OpExp::MINUS, (absyn::Exp*)(yyvsp[0].synTree)); }
#line 1520 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 127 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::IfExp((yyvsp[-2].synTree)->m_pos, (absyn::Exp*)(yyvsp[-2].synTree), new absyn::IntExp((yyvsp[-2].synTree)->m_pos, 1), (absyn::Exp*)(yyvsp[0].synTree)); }
#line 1526 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 128 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::IfExp((yyvsp[-2].synTree)->m_pos, (absyn::Exp*)(yyvsp[-2].synTree), (absyn::Exp*)(yyvsp[0].synTree), new absyn::IntExp((yyvsp[-2].synTree)->m_pos, 0)); }
#line 1532 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 129 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::OpExp((yyvsp[-2].synTree)->m_pos, (absyn::Exp*)(yyvsp[-2].synTree), absyn::OpExp::EQ, (absyn::Exp*)(yyvsp[0].synTree)); }
#line 1538 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 130 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::OpExp((yyvsp[-2].synTree)->m_pos, (absyn::Exp*)(yyvsp[-2].synTree), absyn::OpExp::LT, (absyn::Exp*)(yyvsp[0].synTree)); }
#line 1544 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 131 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::OpExp((yyvsp[-2].synTree)->m_pos, (absyn::Exp*)(yyvsp[-2].synTree), absyn::OpExp::LE, (absyn::Exp*)(yyvsp[0].synTree)); }
#line 1550 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 132 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::OpExp((yyvsp[-2].synTree)->m_pos, (absyn::Exp*)(yyvsp[-2].synTree), absyn::OpExp::GT, (absyn::Exp*)(yyvsp[0].synTree)); }
#line 1556 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 133 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::OpExp((yyvsp[-2].synTree)->m_pos, (absyn::Exp*)(yyvsp[-2].synTree), absyn::OpExp::GE, (absyn::Exp*)(yyvsp[0].synTree)); }
#line 1562 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 134 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::OpExp((yyvsp[-2].synTree)->m_pos, (absyn::Exp*)(yyvsp[-2].synTree), absyn::OpExp::NE, (absyn::Exp*)(yyvsp[0].synTree)); }
#line 1568 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 135 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::AssignExp(0, (absyn::Var*)(yyvsp[-2].synTree), (absyn::Exp*)(yyvsp[0].synTree)); }
#line 1574 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 136 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::CallExp(0, symbol::Symbol::symbol(*(yyvsp[-3].s)), (yyvsp[-1].expList)); delete (yyvsp[-3].s); }
#line 1580 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 137 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::CallExp(0, symbol::Symbol::symbol(*(yyvsp[-2].s)), nullptr); delete (yyvsp[-2].s); }
#line 1586 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 138 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::SeqExp(0, (yyvsp[-1].expList)); }
#line 1592 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 139 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::SeqExp(0, nullptr); }
#line 1598 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 140 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::RecordExp(0, symbol::Symbol::symbol(*(yyvsp[-3].s)), (absyn::FieldExpList*)(yyvsp[-1].synTree)); delete (yyvsp[-3].s); }
#line 1604 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 141 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::RecordExp(0,  symbol::Symbol::symbol(*(yyvsp[-2].s)), nullptr); delete (yyvsp[-2].s); }
#line 1610 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 142 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::ArrayExp(0, symbol::Symbol::symbol(*(yyvsp[-5].s)), (absyn::Exp*)(yyvsp[-3].synTree), (absyn::Exp*)(yyvsp[0].synTree)); delete (yyvsp[-5].s);}
#line 1616 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 143 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::IfExp(0, (absyn::Exp*)(yyvsp[-2].synTree), (absyn::Exp*)(yyvsp[0].synTree)); }
#line 1622 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 144 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::IfExp(0, (absyn::Exp*)(yyvsp[-4].synTree), (absyn::Exp*)(yyvsp[-2].synTree), (absyn::Exp*)(yyvsp[0].synTree)); }
#line 1628 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 145 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::WhileExp(0, (absyn::Exp*)(yyvsp[-2].synTree), (absyn::Exp*)(yyvsp[0].synTree)); }
#line 1634 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 146 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::ForExp(0, new absyn::VarDec(0, symbol::Symbol::symbol(*(yyvsp[-6].s)), new absyn::NameTy(0, symbol::Symbol::symbol("int")), (absyn::Exp*)(yyvsp[-4].synTree)), (absyn::Exp*)(yyvsp[-2].synTree), (absyn::Exp*)(yyvsp[0].synTree)); delete (yyvsp[-6].s); }
#line 1640 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 147 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::BreakExp(0); }
#line 1646 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 148 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::LetExp(0, (absyn::DecList*)(yyvsp[-2].decList), nullptr); }
#line 1652 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 149 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::LetExp(0, (absyn::DecList*)(yyvsp[-3].decList), new absyn::SeqExp(0, (absyn::ExpList*)(yyvsp[-1].expList))); }
#line 1658 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 154 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::SubscriptVar(0, (absyn::Var*)(yyvsp[-3].synTree), (absyn::Exp*)(yyvsp[-1].synTree)); }
#line 1664 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 155 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::FieldVar(0, (absyn::Var*)(yyvsp[-2].synTree), symbol::Symbol::symbol(*(yyvsp[0].s))); delete (yyvsp[0].s); }
#line 1670 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 156 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::SimpleVar(0, symbol::Symbol::symbol(*(yyvsp[0].s))); delete (yyvsp[0].s); }
#line 1676 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 157 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::SubscriptVar(0, new absyn::SimpleVar(0, symbol::Symbol::symbol(*(yyvsp[-3].s))),  (absyn::Exp*)(yyvsp[-1].synTree)); delete (yyvsp[-3].s); }
#line 1682 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 160 "parser.ypp" /* yacc.c:1646  */
    { (yyval.expList) = new absyn::ExpList((absyn::Exp*)(yyvsp[0].synTree), nullptr); }
#line 1688 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 161 "parser.ypp" /* yacc.c:1646  */
    { (yyval.expList) = new absyn::ExpList((absyn::Exp*)(yyvsp[-2].synTree), (absyn::ExpList*)(yyvsp[0].expList)); }
#line 1694 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 164 "parser.ypp" /* yacc.c:1646  */
    { (yyval.expList) = new absyn::ExpList((absyn::Exp*)(yyvsp[0].synTree), nullptr); }
#line 1700 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 165 "parser.ypp" /* yacc.c:1646  */
    { (yyval.expList) = new absyn::ExpList((absyn::Exp*)(yyvsp[-2].synTree), (absyn::ExpList*)(yyvsp[0].expList)); }
#line 1706 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 168 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::FieldExpList(0, symbol::Symbol::symbol(*(yyvsp[-2].s)), (absyn::Exp*)(yyvsp[0].synTree), nullptr); delete (yyvsp[-2].s);}
#line 1712 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 169 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::FieldExpList(0, symbol::Symbol::symbol(*(yyvsp[-4].s)), (absyn::Exp*)(yyvsp[-2].synTree), (absyn::FieldExpList*)(yyvsp[0].synTree)); delete (yyvsp[-4].s); }
#line 1718 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 172 "parser.ypp" /* yacc.c:1646  */
    { (yyval.decList) = new absyn::DecList((absyn::Dec*)(yyvsp[0].synTree), nullptr); }
#line 1724 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 173 "parser.ypp" /* yacc.c:1646  */
    { (yyval.decList) = new absyn::DecList((absyn::Dec*)(yyvsp[-1].synTree), (yyvsp[0].decList)); }
#line 1730 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 176 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = (yyvsp[0].synTree); }
#line 1736 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 177 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = (yyvsp[0].synTree); }
#line 1742 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 178 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = (yyvsp[0].synTree); }
#line 1748 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 181 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = (yyvsp[0].synTree); }
#line 1754 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 182 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::TypeDec((yyvsp[-1].synTree)->m_pos, ((absyn::TypeDec*)(yyvsp[-1].synTree))->m_name, ((absyn::TypeDec*)(yyvsp[-1].synTree))->m_ty, (absyn::TypeDec*)(yyvsp[0].synTree)); }
#line 1760 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 185 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::TypeDec(0, symbol::Symbol::symbol(*(yyvsp[-2].s)), (absyn::Ty*)(yyvsp[0].synTree), nullptr); delete (yyvsp[-2].s); }
#line 1766 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 188 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::NameTy(0, symbol::Symbol::symbol(*(yyvsp[0].s))); delete (yyvsp[0].s); }
#line 1772 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 189 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::RecordTy(0, (absyn::FieldList*)(yyvsp[-1].synTree)); }
#line 1778 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 190 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::RecordTy(0, nullptr); }
#line 1784 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 191 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::ArrayTy(0, symbol::Symbol::symbol(*(yyvsp[0].s))); delete (yyvsp[0].s); }
#line 1790 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 194 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::FieldList(0, symbol::Symbol::symbol(*(yyvsp[-2].s)), symbol::Symbol::symbol(*(yyvsp[0].s)), nullptr); delete (yyvsp[-2].s); delete (yyvsp[0].s); }
#line 1796 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 195 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::FieldList(0,  symbol::Symbol::symbol(*(yyvsp[-4].s)),  symbol::Symbol::symbol(*(yyvsp[-2].s)), (absyn::FieldList*)(yyvsp[0].synTree)); delete (yyvsp[-4].s); delete (yyvsp[-2].s); }
#line 1802 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 199 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::VarDec(0, symbol::Symbol::symbol(*(yyvsp[-2].s)), nullptr, (absyn::Exp*)(yyvsp[0].synTree)); delete (yyvsp[-2].s); }
#line 1808 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 200 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::VarDec(0, symbol::Symbol::symbol(*(yyvsp[-4].s)), new absyn::NameTy(0, symbol::Symbol::symbol(*(yyvsp[-2].s))), (absyn::Exp*)(yyvsp[0].synTree)); delete (yyvsp[-4].s); delete (yyvsp[-2].s); }
#line 1814 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 203 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = (yyvsp[0].synTree); }
#line 1820 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 204 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::FunctionDec((yyvsp[-1].synTree)->m_pos, ((absyn::FunctionDec*)(yyvsp[-1].synTree))->m_name, ((absyn::FunctionDec*)(yyvsp[-1].synTree))->m_params,  ((absyn::FunctionDec*)(yyvsp[-1].synTree))->m_result,   ((absyn::FunctionDec*)(yyvsp[-1].synTree))->m_body, (absyn::FunctionDec*)(yyvsp[0].synTree)); }
#line 1826 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 207 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::FunctionDec(0, symbol::Symbol::symbol(*(yyvsp[-4].s)), nullptr, nullptr, (absyn::Exp*)(yyvsp[0].synTree), nullptr); delete (yyvsp[-4].s); }
#line 1832 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 208 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::FunctionDec(0, symbol::Symbol::symbol(*(yyvsp[-5].s)), (absyn::FieldList*)(yyvsp[-3].synTree), nullptr, (absyn::Exp*)(yyvsp[0].synTree), nullptr); delete (yyvsp[-5].s); }
#line 1838 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 209 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::FunctionDec(0, symbol::Symbol::symbol(*(yyvsp[-6].s)), nullptr, new absyn::NameTy(0, symbol::Symbol::symbol(*(yyvsp[-2].s))), (absyn::Exp*)(yyvsp[0].synTree), nullptr); delete (yyvsp[-6].s); delete (yyvsp[-2].s); }
#line 1844 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 210 "parser.ypp" /* yacc.c:1646  */
    { (yyval.synTree) = new absyn::FunctionDec(0, symbol::Symbol::symbol(*(yyvsp[-7].s)), (absyn::FieldList*)(yyvsp[-5].synTree), new absyn::NameTy(0, symbol::Symbol::symbol(*(yyvsp[-2].s))), (absyn::Exp*)(yyvsp[0].synTree), nullptr); delete (yyvsp[-7].s); delete (yyvsp[-2].s); }
#line 1850 "parser.tab.cpp" /* yacc.c:1646  */
    break;


#line 1854 "parser.tab.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 212 "parser.ypp" /* yacc.c:1906  */



int main() {
  yyparse();
  return 0;
}

