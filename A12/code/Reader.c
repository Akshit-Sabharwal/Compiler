/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2022
* Author: Akshit Sabharwal - Youssef Hamzo
* Professors: Paulo Sousa
************************************************************
 _________________________________
|                                 |
| ........ BOA LANGUAGE ......... |
|     __    __    __    __        |
|    /  \  /  \  /  \  /  \       |
| __/  __\/  __\/  __\/  __\__    |
| _/  /__/  /__/  /__/  /_____|   |
|  \_/ \   / \   / \   / \  \___  |
|       \_/   \_/   \_/   \___o_> |
|                                 | 
| .. ALGONQUIN COLLEGE - 2022F .. |
|_________________________________|

*/
//updates here
/*
***********************************************************
* File name: Reader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
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
* Algorithm: Allocation of memory according to inicial (default) values.
* TODO ......................................................
*	- Adjust datatypes for your LANGUAGE.
*   - Use defensive programming
*	- Check boundary conditions
*	- Check flags.
*************************************************************
*/

ReaderPointer readerCreate(viper_intg size, viper_intg increment, viper_intg mode) {
	ReaderPointer readerPointer;
	/* TO_DO: Defensive programming */
	//add if statement 
	/* TO_DO: Adjust the values according to parameters */
	size = READER_DEFAULT_SIZE;
	increment = READER_DEFAULT_INCREMENT;
	mode = MODE_FIXED;
	readerPointer = (ReaderPointer)calloc(1, sizeof(BufferReader));
	/* TO_DO: Defensive programming */
	readerPointer->content = (viper_char*)malloc(size);
	/* TO_DO: Defensive programming */
	/* TO_DO: Initialize the histogram */
	readerPointer->size = size;
	readerPointer->increment = increment;
	readerPointer->mode = mode;
	/* TO_DO: Initialize flags */
	/* TO_DO: The created flag must be signalized as EMP */
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
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

ReaderPointer readerAddChar(ReaderPointer const readerPointer, viper_char ch) {
	viper_char* tempReader = NULL;
	viper_intg newSize = 0;
	/* TO_DO: Defensive programming */
	if (ch < 0 || ch > 127)
		return NULL;
	if (readerPointer->histogram[ch]++);
	/* TO_DO: Reset Realocation */
	/* TO_DO: Test the inclusion of chars */
	if (readerPointer->position.wrte * (viper_intg)sizeof(viper_char) < readerPointer->size) {
		/* TO_DO: This buffer is NOT full */
	} else {
		/* TO_DO: Reset Full flag */
		switch (readerPointer->mode) {
		case MODE_FIXED:
			return NULL;

		case MODE_ADDIT:
			/* TO_DO: Adjust new size */
			newSize = readerPointer->size + readerPointer->size;
			/* TO_DO: Defensive programming */
			if (newSize < 0)
				return NULL;
			tempReader = realloc(readerPointer->content, newSize);
			if (!tempReader)
				return NULL;
			if (tempReader != readerPointer->content)
				readerPointer->flags |= SET_REL;
			readerPointer->content = tempReader;
			readerPointer->size = newSize;
			break;

		case MODE_MULTI:
			/* TO_DO: Adjust new size */
			newSize = readerPointer->size * readerPointer->size;
			/* TO_DO: Defensive programming */
			if (newSize < 0)
				return NULL;
			tempReader = realloc(readerPointer->content, newSize);
			if (!tempReader)
				return NULL;
			if (tempReader != readerPointer->content)
				readerPointer->flags |= SET_REL;
			readerPointer->content = tempReader;
			readerPointer->size = newSize;
			break;
		default:
			return NULL;
		}
		/* TO_DO: New reader allocation */
		/* TO_DO: Defensive programming */
		/* TO_DO: Check Relocation */
	}
	/* TO_DO: Add the char */
	readerPointer->content[readerPointer->position.wrte++] = ch;
	/* TO_DO: Updates histogram */
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
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
viper_boln readerClear(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Adjust flags original */
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
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
viper_boln readerFree(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return VIPER_FALSE;
	/* TO_DO: Free pointers */
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
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
viper_boln readerIsFull(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Check flag if buffer is FUL */
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
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
viper_boln readerIsEmpty(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Check flag if buffer is EMP */
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
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
viper_boln readerSetMark(ReaderPointer const readerPointer, viper_intg mark) {
	/* TO_DO: Defensive programming */
	if (!readerPointer || mark<0 || mark > readerPointer->position.wrte)
		return VIPER_FALSE;
	/* TO_DO: Adjust mark */
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
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
viper_intg readerPrint(ReaderPointer const readerPointer) {
	viper_intg cont = 0;
	viper_char c;
	/* TO_DO: Defensive programming (including invalid chars) */
	c = readerGetChar(readerPointer);
	/* TO_DO: Check flag if buffer EOB has achieved */
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
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
viper_intg readerLoad(ReaderPointer const readerPointer, FILE* const fileDescriptor) {
	viper_intg size = 0;
	viper_char c;
	/* TO_DO: Defensive programming */
	c = (viper_char)fgetc(fileDescriptor);
	while (!feof(fileDescriptor)) {
		if (!readerAddChar(readerPointer, c)) {
			ungetc(c, fileDescriptor);
			return READER_ERROR;
		}
		c = (char)fgetc(fileDescriptor);
		size++;
	}
	/* TO_DO: Defensive programming */
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
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
viper_boln readerRecover(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Recover positions */
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
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
viper_boln readerRetract(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Retract (return 1 pos read) */
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
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
viper_boln readerRestore(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Restore positions (read/mark) */
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
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
viper_char readerGetChar(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Check condition to read/wrte */
	/* TO_DO: Set EOB flag */
	/* TO_DO: Reset EOB flag */
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
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
viper_char* readerGetContent(ReaderPointer const readerPointer, viper_intg pos) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return content (string) */
	return NULL;
}



/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
viper_intg readerGetPosRead(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return read */
	return 0;
}


/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
viper_intg readerGetPosWrte(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return wrte */
	return 0;
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
viper_intg readerGetPosMark(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return mark */
	return 0;
}


/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
viper_intg readerGetSize(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return size */
	return 0;
}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
viper_intg readerGetInc(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return increment */
	return 0;
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
viper_intg readerGetMode(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return mode */
	return 0;
}


/*
***********************************************************
* Function name: readerGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Flags from Buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
viper_byte readerGetFlags(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return flags */
	return 0;
}


/*
***********************************************************
* Function name: readerShowStat
* Purpose: Returns the number of chars used.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
viper_intg readerShowStat(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Updates the histogram */
	return 0;
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