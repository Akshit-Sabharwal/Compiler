/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa
************************************************************
__________________________________
| .........VIPER LANGUAGE........|
|   \ \        |___  ___|----\   |
|    \ \       / /|  |  |  -  \  |
|     \ \     / / |  |  | | | |  |
|      \ \   / /  |  |  |  -  /  |
|       \ \_/ /   |  |  |  __/   |
|        \   /    |  |  |  |     |
|         \_/  |________|__|     |
|				                 |
| ....ALGONQUIN COLLEGE- 2022F...|
|________________________________|

*/

/*
************************************************************
* File name: parser.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
*************************************************************/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef READER_H_
#include "Reader.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token lookahead;
extern BufferReader* stringLiteralTable;
extern viper_intg line;
extern Token tokenizer();
extern viper_char* keywordTable[];
viper_intg syntaxErrorNumber = 0;

#define STR_LANGNAME	"VIPER"
#define LANG_WRTE		"print("
#define LANG_READ		"input("
#define LANG_MAIN		"main("
#define LANG_DEF		"def"
/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */

/* Constants */
enum KEYWORDS {
	NO_ATTR = -1,
	KW_data,
	KW_code,
	KW_int,
	KW_real,
	KW_string,
	KW_if,
	KW_then,
	KW_else,
	KW_while,
	KW_do,
	KW_def,
	KW_for,
	KW_elif,
	KW_True,
	KW_False,
	KW_return,
	KW_print,
	KW_input
};

/* Function definitions */
viper_void startParser();
viper_void matchToken(viper_intg, viper_intg);
viper_void syncErrorHandler(viper_intg);
viper_void printError();

/* TO_DO: Place ALL non-terminal function declarations */
viper_void codeSession();
viper_void dataSession();
viper_void optVarListDeclarations();
viper_void optionalStatements();
viper_void outputStatement();
viper_void outputVariableList();
viper_void program();
viper_void statement();
viper_void statements();
viper_void statementsPrime();
viper_void inputStatement();
viper_void expression();
viper_void expressions();
viper_void expressionsPrime();
#endif
