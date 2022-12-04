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
//updates here
/*
***********************************************************
* File name: Reader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer/Reader (A12)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * - Please check the "TODO" labels to develop your activity.
 * - Review the functions to use "Defensive Programming".
 *.............................................................................
 */


#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

 /*
 ***********************************************************
 * Function name: readerCreate
 * Purpose: Creates the buffer reader according to capacity, increment
	 factor and operational mode ('f', 'a', 'm')
 * Author: Svillen Ranev / Paulo Sousa
 * History/Versions: S22
 * Called functions: calloc(), malloc()
 * Parameters:
 *   size = initial capacity
 *   increment = increment factor
 *   mode = operational mode
 * Return value: bPointer (pointer to reader)
 * Algorithm: Allocation of memory according to initial (default) values.
 *
 *************************************************************
 */
 /*Char Things remember
 check the Hex Table appropraiate rwange would be 32 and 126, as there are some undefined
 char values
 */
ReaderPointer readerCreate(viper_intg size, viper_intg increment, viper_intg mode) {
	ReaderPointer readerPointer;
	/*  Defensive programming */
	if (size < 0 || (increment < 0)|| size > READER_MAX_SIZE)
		return NULL;

	/*  Adjust the values according to parameters */
	if (increment == 0 && mode != MODE_FIXED) {
		increment = READER_DEFAULT_INCREMENT;

	}

	if (size == 0) {
		size = READER_DEFAULT_SIZE;
		//increment = READER_DEFAULT_INCREMENT;
		//mode = MODE_FIXED;
	}//f a m
	if (mode != MODE_FIXED && mode != MODE_ADDIT && mode != MODE_MULTI)
		return NULL;

	readerPointer = (ReaderPointer)calloc(1, sizeof(BufferReader));
	/*  Defensive programming */
	if (!readerPointer)
		return NULL;

	readerPointer->content = (viper_char*)malloc(size);

	/*  Defensive programming */
	if (!readerPointer->content)
		return NULL;
	/*  Initialize the histogram */
	for (int i = 0; i < NCHAR; i++)
		readerPointer->histogram[i] = 0;

	readerPointer->size = size;
	readerPointer->increment = increment;
	readerPointer->mode = mode;


	/*  Initialize flags */
	/*  The created flag must be signalized as EMP */
	readerPointer->flags = READER_DEFAULT_FLAG | SET_EMP;

	return readerPointer;
}


/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
* 
*  
*************************************************************
*/

ReaderPointer readerAddChar(ReaderPointer const readerPointer, viper_char ch) {
	viper_char* tempReader = NULL;
	viper_intg newSize = 0;
	/*  Defensive programming */
	if (!readerPointer)
		return NULL;

	/*  Reset Realocation */
	readerPointer->flags &= RESET_RLB;
	/*  Test the inclusion of chars */
	if (ch < 0 || ch >= NCHAR)
		return NULL;
	if (readerPointer->position.wrte * (viper_intg)sizeof(viper_char) < readerPointer->size) {
		/*  This buffer is NOT full */
		readerPointer->content[readerPointer->position.wrte++] = ch;
		/*  Updates histogram */

		readerPointer->histogram[ch]++;
		return readerPointer;

	}
	else {
		/*  Reset Full flag */
		switch (readerPointer->mode) {
		case MODE_FIXED:
			return NULL;

		case MODE_ADDIT:
			/*  Adjust new size */
			newSize = readerPointer->size + readerPointer->increment;
			/*  Defensive programming */
			if (newSize < 0)
				return NULL;
			break;
		case MODE_MULTI:
			/*  Adjust new size */
			newSize = readerPointer->size * readerPointer->increment;
			/*  Defensive programming */
			if (newSize < 0)
				return NULL;
			break;
		default:
			return NULL;
		}
		/*  New reader allocation */
		tempReader = realloc(readerPointer->content, newSize);
		if (!tempReader)
			return NULL;
		if (tempReader != readerPointer->content)
			readerPointer->flags |= SET_RLB;

		readerPointer->content = tempReader;
		readerPointer->size = newSize;

	}
	/*  Add the char */
	readerPointer->content[readerPointer->position.wrte++] = ch;
	/*  Updates histogram */

	readerPointer->histogram[ch]++;
	return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* 
*   
*************************************************************
*/
viper_boln readerClear(ReaderPointer const readerPointer) {
	/*  Defensive programming */
	if (!readerPointer)
		return VIPER_FALSE;
	/*  Adjust flags original */
	free(readerPointer->content);
	readerPointer->flags = READER_DEFAULT_FLAG;

	return VIPER_TRUE;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* 
* 
*************************************************************
*/
viper_boln readerFree(ReaderPointer const readerPointer) {
	/*  Defensive programming */
	if (!readerPointer)
		return VIPER_FALSE;
	/*  Free pointer */
	free(readerPointer);
	return VIPER_TRUE;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* 
*  
*************************************************************
*/
viper_boln readerIsFull(ReaderPointer const readerPointer) {
	/*  Defensive programming */
	if (!readerPointer)
		return VIPER_FALSE;
	/*  Check flag if buffer is FUL */
	if (readerPointer->flags == CHECK_FUL)
		return VIPER_TRUE;

	return VIPER_FALSE;
}


/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* 
*   
*************************************************************
*/
viper_boln readerIsEmpty(ReaderPointer const readerPointer) {
	/*  Defensive programming */
	if (!readerPointer)
		return VIPER_FALSE;
	/*  Check flag if buffer is EMP */
	if (readerPointer->flags == CHECK_EMP)
		return VIPER_TRUE;
	return VIPER_FALSE;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* 
*  
*************************************************************
*/
viper_boln readerSetMark(ReaderPointer const readerPointer, viper_intg mark) {
	/*  Defensive programming */
	if (!readerPointer || mark<0 || mark > readerPointer->position.wrte)
		return VIPER_FALSE;
	/*  Adjust mark */
	readerPointer->position.mark = mark;
	return VIPER_TRUE;
}


/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
* 
*   
*************************************************************
*/
viper_intg readerPrint(ReaderPointer const readerPointer) {
	viper_intg cont = 0;
	viper_char c;
	/*  Defensive programming (including invalid chars) */
	if (!readerPointer)
		return READER_ERROR;
	c = readerGetChar(readerPointer);
	if (c < 0 || c> 127)
		return READER_ERROR;
	/*  Check flag if buffer End of buffer (EOB) has achieved */
	if (readerIsFull(readerPointer)) {
		printf("Reader is Full");
	}
	while (cont < readerPointer->position.wrte) {
		cont++;
		printf("%c", c);
		c = readerGetChar(readerPointer);
	}
	return cont;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* 
*
*************************************************************
*/
viper_intg readerLoad(ReaderPointer const readerPointer, FILE* const fileDescriptor) {
	viper_intg size = 0;
	viper_char c;
	/*  Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	c = (viper_char)fgetc(fileDescriptor);
	while (!feof(fileDescriptor)) {
		if (!readerAddChar(readerPointer, c)) {
			ungetc(c, fileDescriptor);
			return READER_ERROR;
		}
		c = (char)fgetc(fileDescriptor);
		size++;
	}
	/*  Defensive programming */
	return size;
}


/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
* 
*  
*************************************************************
*/
viper_boln readerRecover(ReaderPointer const readerPointer) {
	/*  Defensive programming */
	if (!readerPointer)
		return VIPER_FALSE;
	/* Recover positions */
	readerPointer->position.mark = 0;
	readerPointer->position.read = 0;
	return VIPER_TRUE;
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* 
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
viper_boln readerRetract(ReaderPointer const readerPointer) {
	/*  Defensive programming */
	if (!readerPointer)
		return VIPER_FALSE;
	/*  Retract (return 1 pos read) */
	readerPointer->position.read--;
	return VIPER_TRUE;
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* 
*   
*************************************************************
*/
viper_boln readerRestore(ReaderPointer const readerPointer) {
	/*  Defensive programming */

	if (!readerPointer)
		return VIPER_FALSE;
	/*  Restore positions (read/mark) */
	readerPointer->position.read = readerPointer->position.mark;
	return VIPER_TRUE;
}



/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
* 
*   
*************************************************************
*/
viper_char readerGetChar(ReaderPointer const readerPointer) {
	/*  Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/*  Check condition to read/wrte */
	if (readerPointer->position.read == readerPointer->position.wrte)
	{
		readerPointer->flags = SET_EMP;
		return 0;
	}
	else
		readerPointer->flags &= RESET_EMP;
	/*  Reset EOB flag */
	return readerPointer->content[readerPointer->position.read++];
}


/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* 
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
viper_char* readerGetContent(ReaderPointer const readerPointer, viper_intg pos) {
	/*  Defensive programming */
	if (!readerPointer)
		return NULL;
	/*  Return content (string) */
	return readerPointer->content + pos;
}



/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
*
*************************************************************
*/
viper_intg readerGetPosRead(ReaderPointer const readerPointer) {
	if (!readerPointer)
		return READER_ERROR;
	
	return readerPointer->position.read;
}


/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* 
*  
*************************************************************
*/
viper_intg readerGetPosWrte(ReaderPointer const readerPointer) {
	if (!readerPointer)
		return READER_ERROR;
	
	return readerPointer->position.wrte;
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* 
*   
*************************************************************
*/
viper_intg readerGetPosMark(ReaderPointer const readerPointer) {
	if (!readerPointer)
		return READER_ERROR;
	
	return readerPointer->position.mark;
}


/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
*
*	
*************************************************************
*/
viper_intg readerGetSize(ReaderPointer const readerPointer) {
	if (!readerPointer)
		return READER_ERROR;

	return readerPointer->size;

}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
*
*************************************************************
*/
viper_intg readerGetInc(ReaderPointer const readerPointer) {
	
	if (!readerPointer)
		return READER_ERROR;
	
	return readerPointer->increment;
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
* 
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
viper_intg readerGetMode(ReaderPointer const readerPointer) {
	/*  Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/*  Return mode */
	return readerPointer->mode;
}


/*
***********************************************************
* Function name: readerGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Flags from Buffer.
*
*************************************************************
*/
viper_byte readerGetFlags(ReaderPointer const readerPointer) {
	if (!readerPointer)
		return 0;
	
	return readerPointer->flags;
}


/*
***********************************************************
* Function name: readerShowStat
* Purpose: Returns the number of chars used.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars.
* 
*************************************************************
*/
viper_intg readerShowStat(ReaderPointer const readerPointer) {
	/*  Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/*  Updates the histogram */
	int cnt = 0;
	for (int i = 0; i < NCHAR; i++) {
		if (readerPointer->histogram[i] > 0) {
			//This is my test file.	
			cnt++;
		}
	}
	return cnt;
}

/*
*New function: print the histogram from the content
*/
/*viper_void readerPrintHistogram(ReaderPointer const readerPointer) {
	viper_intg counter = 0;
	viper_intg numChars = 0;
	viper_char ch = '0';
	for (counter = 0; counter < NHCAR; counter++) {
		numChars = readerPointer->histogram[counter];
		if (numChars > 0) {
			ch = readerPointer->content[counter];
			printf("%s%d%s%d%s", "Reader[", ch, "]=", numChars, "\n");
		}
	}
}
*/