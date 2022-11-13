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
|   \ \        |___  ___|    \   |
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
* File name: compilers.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A12, A22, A32.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file defines the functions called by main function.
* Function list: mainReader(), mainScanner(), mainParser().
*************************************************************/

#ifndef COMPILERS_H_
#define COMPILERS_H_

#define DEBUG 0

/*
 * ............................................................................
 * ADVICE 1:
 * Please check the "TODO" labels to develop your activity.
 *
 * ADVICE 2: This file must be updated according to each assignment
 * (see the progression: reader > scanner > parser).
 * ............................................................................
 */
 
/* Logical constants - adapt for your language */
#define VIPER_TRUE  1
#define VIPER_FALSE 0

/*
------------------------------------------------------------
Data types definitions
NOTE: Some types may not be directly used by your language,
		but they can be necessary for conversions.
------------------------------------------------------------
*/
/* TO_DO: Define your typedefs */
typedef char			viper_char;
typedef int				viper_intg;
typedef float			viper_real;
typedef void			viper_void;

typedef unsigned char	viper_boln;
typedef unsigned char	viper_byte;

typedef const           viper_const;
typedef long			viper_long;
typedef double			viper_doub;

/*
------------------------------------------------------------
Programs:
1: Reader - invokes MainReader code
2: Scanner - invokes MainScanner code
3: Parser - invokes MainParser code
------------------------------------------------------------
*/
enum PROGRAMS {
	PGM_READER	= 'R',
	PGM_SCANNER = 'S',
	PGM_PARSER	= 'P'
};

/*
------------------------------------------------------------
Main functions signatures
(Code will be updated during next assignments)
------------------------------------------------------------
*/
viper_intg mainReader  (viper_intg argc, viper_char** argv);

viper_intg mainScanner (viper_intg argc, viper_char** argv);
/*
viper_intg mainParser  (viper_intg argc, viper_char** argv);
*/
viper_void printLogo();


#endif
