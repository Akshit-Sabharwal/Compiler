/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2022
* Author: Svillen Ranev - Paulo Sousa
* Modified by: Youssef Hamzo - Akshit Sabharwal
* Lab Section: 301
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
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

 /* TIP: Do not change pragmas, unless necessary .......................................*/
 /*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
 /*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

 /* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'f', /* Fixed mode (constant size) */
	MODE_ADDIT = 'a', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'm'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR (-1)						/* General error message */
#define READER_TERMINATOR '\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG 0x00 	/* (0000.0000)_2 = (000)_10 */
/* TO_DO: BIT 3: FUL = Full */
/* TO_DO: BIT 2: EMP: Empty */
/* TO_DO: BIT 1: REL = Relocation */
/* TO_DO: BIT 0: END = EndOfBuffer */

#define SET_END 0x01 /*0000.0001 - OR Operator*/
#define RESET_END 0xFE /*1111.1110 - AND Operator*/
#define CHECK_END SET_END /*AND Operator*/

#define SET_RLB 0x02 /*1111.0010 - OR Operator*/
#define RESET_RLB 0xFD /*1111.1101 - AND Operator*/
#define CHECK_RLB SET_REL /*AND Operator*/


#define SET_EMP 0x04   /*0000.0100*/ 
#define RESET_EMP  0xFB   /*1111.1011*/
#define CHECK_EMP SET_EMP 

#define SET_FUL    0x08    /*0000.1000*/
#define RESET_FUL   0xF7   /*1111.0111*/
#define CHECK_FUL  SET_FUL

#define NCHAR				128			/* Chars from 0 to 127 */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* TODO: Adjust datatypes */

/* Offset declaration */
typedef struct position {
	viper_intg mark;			/* the offset to the mark position (in chars) */
	viper_intg read;			/* the offset to the get a char position (in chars) */
	viper_intg wrte;			/* the offset to the add chars (in chars) */
} Position;

/* Buffer structure */
typedef struct bufferReader {
	viper_char* content;			/* pointer to the beginning of character array (character buffer) */
	viper_intg	size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	viper_intg	increment;			/* character array increment factor */
	viper_intg	mode;				/* operational mode indicator */
	viper_byte	flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Position	position;			/* Offset / position field */
	viper_intg	histogram[NCHAR];	/* Statistics of chars */
} BufferReader, * ReaderPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
ReaderPointer	readerCreate(viper_intg, viper_intg, viper_intg);
ReaderPointer	readerAddChar(ReaderPointer const, viper_char);
viper_boln		readerClear(ReaderPointer const);
viper_boln		readerFree(ReaderPointer const);
viper_boln		readerIsFull(ReaderPointer const);
viper_boln		readerIsEmpty(ReaderPointer const);
viper_boln		readerSetMark(ReaderPointer const, viper_intg);
viper_intg		readerPrint(ReaderPointer const);
viper_intg		readerLoad(ReaderPointer const, FILE* const);
viper_boln		readerRecover(ReaderPointer const);
viper_boln		readerRetract(ReaderPointer const);
viper_boln		readerRestore(ReaderPointer const);
/* Getters */
viper_char		readerGetChar(ReaderPointer const);
viper_char* readerGetContent(ReaderPointer const, viper_intg);
viper_intg		readerGetPosRead(ReaderPointer const);
viper_intg		readerGetPosWrte(ReaderPointer const);
viper_intg		readerGetPosMark(ReaderPointer const);
viper_intg		readerGetSize(ReaderPointer const);
viper_intg		readerGetInc(ReaderPointer const);
viper_intg		readerGetMode(ReaderPointer const);
viper_byte		readerGetFlags(ReaderPointer const);
viper_intg		readerShowStat(ReaderPointer const);

#endif