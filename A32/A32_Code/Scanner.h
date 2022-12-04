/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa
************************************************************
*/

/*
************************************************************
* File name: scanner.h
* Compiler: MS Visual Studio 2022
* Author: Paulo Sousa
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A22, A32.
* Date: Jul 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */
#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	MNID_T,		/*  1: Method name identifier token (end with: left parenthesis ) */
	STR_T,		/*  2: String literal token */
	LPR_T,		/*  3: Left parenthesis token */
	RPR_T,		/*  4: Right parenthesis token */
	LBR_T,		/*  5: Left brace token */
	RBR_T,		/*  6: Right brace token */
	KW_T,		/*  7: Keyword token */
	EQS_T,       /* 8: Assignment operator sign =   */
	EOS_T,		/*  8: End of statement (\n) */
	RTE_T,		/*  9: Run-time error token */
	INL_T,		/* 10: Integer Literal token */
	SEOF_T,		/* 11: Source end-of-file token */
	FNL_T,      /* 12: Float point Number Literal*/
	VAR_T,       /*13: Variable Literal Token */
	PER_T,		 /*14: Period Literal Token*/
	ARI_T,		/*15: Arithemetic Token*/
	REL_T,		/*16: Logic Token*/
	CLN_T,       /*17: Colon (:) Token*/
	LOG_T		/*18: Logical operator*/
};
/*Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	viper_intg codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	viper_intg intValue;						/* integer literal attribute (value) */
	viper_intg keywordIndex;					/* keyword index in the keyword table */
	viper_intg contentString;				/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	viper_real floatValue;					/* floating-point literal attribute (value) */
	viper_char idLexeme[VID_LEN + 1];		/* variable identifier token attribute */
	viper_char errLexeme[ERR_LEN + 1];		/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	viper_byte flags;			/* Flags information */
	union {
		viper_intg intValue;				/* Integer value */
		viper_real floatValue;			/* Float value */
		viper_char* stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	viper_intg code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner
 *  '=' , ' ' , '(' , ')' , '{' , '}' , == , <> , '>' , '<' , ';', 
 *  white space, #comment\n , ',' , ';' , '-' , '+' , '*' , '/', # , 
 *  .&., .|. , .!. , SEOF.
 */

/* TO_DO: Define lexeme FIXED classes */

/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
#define CHRCOL2 '_'
#define CHRCOL3 '.'
#define CHRCOL4 '('
#define CHRCOL5 '\n'
#define CHRCOL6 '"'
#define CHRCOL7 '#'
/* These constants will be used on VID / MID function */
#define MNIDPREFIX '('

/* TO_DO: Error states and illegal state */
#define FS		100		/* Illegal state */
#define ESWR	101		/* Error state with retract */
#define ESNR	102		/* Error state with no retract */

 /* TO_DO: State transition table definition */
#define TABLE_COLUMNS 9

/* TO_DO: Transition table - type of states defined in separate table */
static viper_intg transitionTable[][TABLE_COLUMNS] = {
	/*   [A-z] , [0-9],    _,  .,      (,    \n,   ",    #    other
		   L(0),  D(1), U(2),  P(3)  M(4), N(5), Q(6), C(7),  O(8) */
		{     1,     8, ESNR,  ESNR, ESNR, ESNR,    4,     6,   ESNR}, // S0: NOAS
		{     1,     1,    1,     3,    2,    3,    3,     3,      3}, // S1: NOAS
		{    FS,    FS,   FS,   FS,   FS,   FS,    FS,    FS,     FS}, // S2: ASNR (MVID)
		{    FS,    FS,   FS,   FS,   FS,   FS,    FS,    FS,     FS}, // S3: ASWR (VARIABLE)
		{     4,     4,    4,    4,    4,    4,     5,     4,	   4}, // S4: NOAS 
		{    FS,    FS,   FS,   FS,   FS,   FS,    FS,	  FS,  	  FS}, // S5: ASNR (SL)
		{    6,      6,    6,    6,    6,    7,     6,	   6,	   6}, // S6: NOAS
		{    FS,    FS,   FS,   FS,   FS,   FS,    FS,	  FS,	  FS},  // S7: ASNR (COMMENTS
		{     9,     8,    9,    10,    9,	 9,     9,	   9,	  9,}, // S8: NOAS 
		{    FS,    FS,   FS,   FS,   FS,   FS,    FS,	  FS,	  FS}, // S9: ASWR (INTEGER)
		{    11,    10,   11,   11,   11,   11,    11,	  11,	  11}, // S10: NOAS 
		{    FS,    FS,   FS,   FS,   FS,   FS,    FS,	  FS,	  FS},  // S11: ASWR (FLOAT)
};

/* Define accepting states types */
#define NOAS	0		/* not accepting state */
#define ASNR	1		/* accepting state with no retract */
#define ASWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static viper_intg stateType[] = {
	NOAS, /* 00 */
	NOAS, /* 01 */
	ASNR, /* 02 - MVID */
	ASWR, /* 03 - VARIABLE1*/
	NOAS, /* 04  */
	ASNR, /* 05  - STRING*/
	NOAS, /*  06*/
	ASNR, /* 07  COMMENTS*/
	NOAS,  /* 08  */
	ASWR,  /* 09 INTEGER*/
	NOAS, /* 10 */
	ASWR,  /* 11 FLOAT*/
	ASNR, /* 12 (Err1 - no retract) */
	ASWR  /* 13 (Err2 - retract) */
};



/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
viper_intg startScanner(ReaderPointer psc_buf);
static viper_intg nextClass(viper_char c);			/* character class function */
static viper_intg nextState(viper_intg, viper_char);		/* state machine function */

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(viper_char* lexeme);

/* Declare accepting states functions */
Token funcSL	(viper_char lexeme[]);
Token funcID	(viper_char lexeme[]);
Token funcKEY	(viper_char lexeme[]);
Token funcErr	(viper_char lexeme[]);
Token funcVar   (viper_char lexeme[]);
Token funcIL  (viper_char lexeme[]);
Token funcFloat (viper_char lexeme[]);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

 /* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	funcID,		/* MNID	[02] */
	funcID,		/* VARIABLE  [03] */
	NULL,		/* -    [04] */
	funcSL,		/* SL   [05] */
	NULL,	    /* - [06] */
	NULL,		/* Comment [07] */
	NULL,	    /*-  [08] */
	funcIL,	/* -Integer    [09] */
	NULL,		/* -   [10] */
	funcFloat,	/* Float [11] */
	funcErr,	/* Err1 [12]*/
	funcErr     /* Err2 [13] - without retraction*/
};


/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 18

/* TO_DO: Define the list of keywords */
static viper_char* keywordTable[KWT_SIZE] = {
		"data",
	"code",
	"int",
	"real",
	"string",
	"if",
	"then",
	"else",
	"while",
	"do",
	"def",
	"for",
	"elif",
	"True",
	"False",
	"return",
	"print",
	"input"
};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	viper_char indentationCharType;
	viper_intg indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

#endif
