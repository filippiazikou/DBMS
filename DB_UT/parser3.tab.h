/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TK_ID = 258,
     TK_CONST_INT = 259,
     TK_CONST_REAL = 260,
     TK_SQSTRING = 261,
     TK_DQSTRING = 262,
     TK_OPER_EQUAL = 263,
     TK_OPER_GRE = 264,
     TK_OPER_LESS = 265,
     TK_OPER_DIF = 266,
     TK_OPER_GEQ = 267,
     TK_OPER_LEQ = 268,
     TK_OPER_LIKE = 269,
     TK_SEP_SEM = 270,
     TK_SEP_FSTOP = 271,
     TK_SEP_RPAR = 272,
     TK_SEP_LPAR = 273,
     TK_SEP_COMMA = 274,
     TK_matched = 275,
     TK_SELECT = 276,
     TK_CREATE = 277,
     TK_BUILDINDEX = 278,
     TK_DESTROY = 279,
     TK_MVIEW = 280,
     TK_QUIT = 281,
     TK_DELETE = 282,
     TK_INSERT = 283,
     TK_INTO = 284,
     TK_WHERE = 285,
     TK_RECORDS = 286,
     TK_OF = 287,
     TK_AND = 288,
     TK_AS = 289
   };
#endif
/* Tokens.  */
#define TK_ID 258
#define TK_CONST_INT 259
#define TK_CONST_REAL 260
#define TK_SQSTRING 261
#define TK_DQSTRING 262
#define TK_OPER_EQUAL 263
#define TK_OPER_GRE 264
#define TK_OPER_LESS 265
#define TK_OPER_DIF 266
#define TK_OPER_GEQ 267
#define TK_OPER_LEQ 268
#define TK_OPER_LIKE 269
#define TK_SEP_SEM 270
#define TK_SEP_FSTOP 271
#define TK_SEP_RPAR 272
#define TK_SEP_LPAR 273
#define TK_SEP_COMMA 274
#define TK_matched 275
#define TK_SELECT 276
#define TK_CREATE 277
#define TK_BUILDINDEX 278
#define TK_DESTROY 279
#define TK_MVIEW 280
#define TK_QUIT 281
#define TK_DELETE 282
#define TK_INSERT 283
#define TK_INTO 284
#define TK_WHERE 285
#define TK_RECORDS 286
#define TK_OF 287
#define TK_AND 288
#define TK_AS 289




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 78 "parser3.y"
{
		char stringBuffer[150];
		char *string;
		char character;
		char *charPtr;
		command cmd;
		attribute attr;
	}
/* Line 1489 of yacc.c.  */
#line 126 "parser3.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

