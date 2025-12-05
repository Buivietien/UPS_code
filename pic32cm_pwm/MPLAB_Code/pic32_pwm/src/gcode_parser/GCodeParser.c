/*
MIT License

Copyright (c) 2021 Terence Golla

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <gcode_parser/GCodeParser.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include "definitions.h"

// #define GCODEPARSER_MAX_LINE_SIZE 256 // Maximun GCode line size
// extern int GcodeParser_lineCharCount;
// extern char GcodeParser_line[GCODEPARSER_MAX_LINE_SIZE + 2];
// extern char* GcodeParser_comments;
// extern char* GcodeParser_lastComment;
// extern bool GcodeParser_blockDelete;
// extern bool GcodeParser_beginEnd;
// extern bool GcodeParser_completeLineIsAvailableToParse;

int GcodeParser_lineCharCount;
char GcodeParser_line[GCODEPARSER_MAX_LINE_SIZE + 2];
char* GcodeParser_comments;
char* GcodeParser_lastComment;
bool GcodeParser_blockDelete;
bool GcodeParser_beginEnd;
bool GcodeParser_completeLineIsAvailableToParse;

// void GcodeParser_Initialize();
// // GCodeParser();
// bool GcodeParser_AddCharToLine(char c);
// void GcodeParser_ParseLine();
// void GcodeParser_ParseLine_char(char* gCode);
// void GcodeParser_RemoveCommentSeparators();

// int GcodeParser_FindWord(char letter);
// bool GcodeParser_HasWord(char letter);
// bool GcodeParser_IsWord(char letter);
// bool GcodeParser_NoWords();

// double GcodeParser_GetWordValue(char letter);
 /// <summary>
 /// Initializizes class.
 /// </summary>
void GcodeParser_Initialize()
{
	GcodeParser_lineCharCount = 0;
	GcodeParser_line[GcodeParser_lineCharCount] = '\0';
	GcodeParser_comments = GcodeParser_line;
	GcodeParser_lastComment = GcodeParser_comments;
	GcodeParser_blockDelete = false;
	GcodeParser_beginEnd = false;
	GcodeParser_completeLineIsAvailableToParse = false;
}

/// <summary>
/// Class constructor.
/// </summary>
/// <remark>
/// The G Code language is based on the RS274/NGC language. The G Code 
/// language is based on lines of code. Each line (also called a 'block')
/// may include commands to do several different things. Lines of code
/// may be collected in a file to make a program.
/// </remark>

/// <summary>
/// Adds a character to the line to be parsed.
/// </summary>
/// <param name="letter">The character to add.</param>
/// <returns>True if a complete line is available to parse.</returns>
/// <remarks>Adding a character after a CR/LF (\r\n - Windows) or LF (\n - Linux, Mac) have been added will reset the line buffer.</remarks>
bool GcodeParser_AddCharToLine(volatile char temp_char)
{
	char c = temp_char;
	// Determine is a new line is being added.
	// if (GcodeParser_completeLineIsAvailableToParse)
	// 	GcodeParser_Initialize();

	// Look for end of line. CRLF (\r\n) or just LF (\n).
	if (c == '\r' || c == '\n')
	{
		if (c == '\n' || (uint8_t)c == 0xa) // Ignore CR (\r)
			GcodeParser_completeLineIsAvailableToParse = true;
	}
	else
	{
		//Ascii lowercase to upper case
		c = toupper(c);
		// Add character to line.
		GcodeParser_line[GcodeParser_lineCharCount] = c;
		GcodeParser_lineCharCount++;

		// Deal with buffer overflow by initializing. TODO: Need a better solution.  i.e. Throw error?
		if (GcodeParser_lineCharCount > GCODEPARSER_MAX_LINE_SIZE)
			GcodeParser_Initialize();

		GcodeParser_line[GcodeParser_lineCharCount] = '\0';
	}

	return GcodeParser_completeLineIsAvailableToParse;
}

/// <summary>
/// Parses the line passed removing spaces, tabs and comments. Comments are shifted to the end of the line buffer.
/// </summary>
void GcodeParser_ParseLine_char(char* gCode)
{
	GcodeParser_Initialize();

  int pointer = 0;
  while (gCode[pointer] != '\0')
  {
	  GcodeParser_AddCharToLine(gCode[pointer]);
	  pointer = pointer + 1;
  }
  	
  GcodeParser_AddCharToLine('\n');
  GcodeParser_ParseLine();
}


/// <summary>
/// Parses the line removing spaces, tabs and comments. Comments are shifted to the end of the line buffer.
/// </summary>
void GcodeParser_ParseLine()
{
	int lineLength = strlen(GcodeParser_line);
	GcodeParser_line[lineLength + 1] = '\0';

	int pointer = 0;
	bool openParentheseFound = false;
	bool semicolonFound = false;
	int correctCommentsPointerBy = 0;

	while (GcodeParser_line[pointer] != '\0')
	{
		char c = GcodeParser_line[pointer];

		// Look for start of comment.
		if (!semicolonFound && c == '(')
			openParentheseFound = true; // Open parenthese... start of comment.

		if (!openParentheseFound && c == ';')
			semicolonFound = true; // Semicolon... start of comment to end of line.

		// If we are inside a comment, we need to move it to the end of the buffer in order to seperate it.
		if (openParentheseFound || semicolonFound)
		{
			// Shift line left.
			for (int i = pointer; i < lineLength; i++)
			{
				GcodeParser_line[i] = GcodeParser_line[i + 1];
			}
			GcodeParser_line[lineLength] = c;
		}
		else
		{
			// Spaces and tabs are allowed anywhere on a line of code and do not change the meaning of 
			// the line, except inside comments. Remove spaces and tabs except in comments. 
			if (c == ' ' || c == '\t')
			{
				int removeCharacterPointer = pointer;

				while (GcodeParser_line[removeCharacterPointer] != '\0')
				{
					GcodeParser_line[removeCharacterPointer] = GcodeParser_line[removeCharacterPointer + 1];

					removeCharacterPointer++;
				}

				correctCommentsPointerBy++;
			}
			else
				pointer++;
		}

		// Look for end of comment.
		if (!semicolonFound && c == ')')
		{
			openParentheseFound = false;

			// Is this the end of the comment? Scan forward for second closing parenthese, but no opening parenthese first.
			int scanAheadPointer = pointer;

			while (GcodeParser_line[scanAheadPointer] != '\0')
			{
				if (GcodeParser_line[scanAheadPointer] == '(')
					break;

				if (GcodeParser_line[scanAheadPointer] == ')')
				{
					openParentheseFound = true;
					break;
				}

				scanAheadPointer++;
			}
		}
	}

	// Set pointer to comments.
	GcodeParser_comments = GcodeParser_line + strlen(GcodeParser_line) + correctCommentsPointerBy + 1;
	GcodeParser_lastComment = GcodeParser_comments;

	// There are several 'active' comments which look like comments but cause some action, like
	// '(debug,..)' or '(print,..)'. If there are several comments on a line, only the last comment
	// will be interpreted according to these rules. For this reason there is a pointer to the last comment.
	pointer = 0;
	openParentheseFound = false;

	while (GcodeParser_comments[pointer] != '\0')
	{
		char c = GcodeParser_comments[pointer];

		// Open parenthese... start of comment.
		if (c == '(')
		{
			GcodeParser_lastComment = GcodeParser_comments + pointer;
			openParentheseFound = true; 
		}

		// Semicolon... start of comment to end of line, the last comment.
		if (!openParentheseFound && c == ';')
		{
			GcodeParser_lastComment = GcodeParser_comments + pointer;
			break;
		}

		// Look for end of comment.
		if (c == ')')
		{
			openParentheseFound = false;

			// Is this the end of the comment? Scan forward for second closing parenthese, but no opening parenthese first.
			int scanAheadPointer = pointer + 1;

			while (GcodeParser_comments[scanAheadPointer] != '\0')
			{
				if (GcodeParser_comments[scanAheadPointer] == '(')
					break;

				if (GcodeParser_comments[scanAheadPointer] == ')')
				{
					openParentheseFound = true;
					break;
				}

				scanAheadPointer++;
			}
		}

		pointer++;
	}

	// The optional block delete character the slash '/' when placed first on a line can be used
	// by some user interfaces to skip lines of code when needed.
	GcodeParser_blockDelete = (GcodeParser_line[0] == '/');

	// The '%' is used to demarcate the beginning (first line) and end (last line) of the program. It is optional if the file has an 'M2' or 'M30'. 
	GcodeParser_beginEnd = (GcodeParser_line[0] == '%');
	
	//Here is where I should reset GcodeParser
	void GcodeParser_Initialize();
}

/// <summary>
/// Removes the comment seperators for comments and last comment along with any leading spaces.
/// </summary>
/// <remark>Once removed they cannot be replaced.</remark>
void GcodeParser_RemoveCommentSeparators()
{
	int commentsLength = strlen(GcodeParser_comments);

	int pointer = 0;
	bool openParentheseFound = false;
	int correctCommentsPointerBy = 0;

	while (GcodeParser_comments[pointer] != '\0')
	{
		char c = GcodeParser_comments[pointer];

		// Look for start of comment.
		if (c == '(')
		{
			GcodeParser_comments[pointer] = ' ';
			openParentheseFound = true; // Open parenthese... start of comment.
		}

		if (!openParentheseFound && c == ';')
		{
			GcodeParser_comments[pointer] = ' ';
			break;
		}

		// Look for end of comment.
		if (c == ')')
		{
			openParentheseFound = false;

			// Is this the end of the comment? Scan forward for second closing parenthese, but no opening parenthese first.
			int scanAheadPointer = pointer + 1;

			while (GcodeParser_comments[scanAheadPointer] != '\0')
			{
				if (GcodeParser_comments[scanAheadPointer] == '(')
					break;

				if (GcodeParser_comments[scanAheadPointer] == ')')
				{
					openParentheseFound = true;
					break;
				}

				scanAheadPointer++;
			}

			if (!openParentheseFound)
			{
				// Shift line left.
				for (int i = pointer; i < commentsLength; i++)
				{
					GcodeParser_comments[i] = GcodeParser_comments[i + 1];
				}
			}
			else
				pointer++;
		}
		else
			pointer++;
	}

	while (GcodeParser_comments[0] == ' ')
	{
		// Shift pointer right
		GcodeParser_comments = GcodeParser_comments + 1;
	}

	while (GcodeParser_lastComment[0] == ' ')
	{
		// Shift pointer right
		GcodeParser_lastComment = GcodeParser_lastComment + 1;
	}
}

/// <summary>
/// Looks for a word in the line.
/// </summary>
/// <param name="c">The letter of the word to look for in the line.</param>
/// <returns>A pointer to where the word starts.  Points to \0 if the word was not found.</returns>
int GcodeParser_FindWord(char letter)
{
	int pointer = 0;
	bool openParentheseFound = false;
	bool semicolonFound = false;

	while (GcodeParser_line[pointer] != '\0')
	{
		// Look for the word.
		if (letter == GcodeParser_line[pointer])
		{
			return pointer;
		}

		pointer++;
	}

	return pointer;
}

/// <summary>
/// Looks through the code block to determin if a word exist.
/// </summary>
/// <param name="letter">The letter of the GCode word.</param>
/// <returns>True if the word exist on the line.</returns>
bool GcodeParser_HasWord(char letter)
{
	if (GcodeParser_IsWord(letter))
	{
		int pointer = GcodeParser_FindWord(letter);

		if (GcodeParser_line[pointer] == '\0')
		{
			return false;
		}
	}

	return true;
}

char wordLetter[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '\0' };

/// <summary>
/// Determine if the letter provided represents a valid GCode word.
/// </summary>
/// <param name="letter">The letter to be tested.</param>
/// <returns>True if the letter represents a valid word.</returns>
/// <remark>
/// Words may begin with any of the letters shown in the following
/// Table. The table includes N, @, ^ and / for completeness, even 
/// though, line numbers, polar coordinates and the block delete  
/// character are not considered words. Several letters (I, J, K,
/// L, P, R) may have different meanings in different contexts.
/// Letters which refer to axis names are not valid on a machines
/// which do not have the corresponding axis.
/// 
/// A - A axis of machine.
/// B - B axis of machine.
/// C - C axis of machine.
/// D - Tool radius compensation number.
/// F - Feed rate.
/// G - General function(See table Modal Groups).
/// H - Tool length offset index.
/// I - X offset for arcsand G87 canned cycles.
/// J - Y offset for arcsand G87 canned cycles.
/// K - Z offset for arcsand G87 canned cycles. Spindle - Motion Ratio for G33 synchronized movements.
/// L - generic parameter word for G10, M66and others.
/// M - Miscellaneous function(See table Modal Groups).
/// N - Line number. Line numbers are not considered words.
/// P - Dwell time in canned cyclesand with G4. Key used with G10.
/// Q - Feed increment in G73, G83 canned cycles.
/// R - Arc radius or canned cycle plane.
/// S - Spindle speed.
/// T - Tool selection.
/// U - U axis of machine.
/// V - V axis of machine.
/// W - W axis of machine.
/// X - X axis of machine.
/// Y - Y axis of machine.
/// Z - Z axis of machine
/// @ - Polar coordinate for the distance. Polar coordinates are not considered words.
/// ^ - Polar coordinate for the angle. Polar coordinates are not considered words.
/// / - The block delete character causes the processor to skips the line and is not considered a word.
/// % - Indicated the beginning and end of a program and is not considered a word.
/// </remark>
bool GcodeParser_IsWord(char letter)
{	
	int pointer = 0;
	while (wordLetter[pointer] != '\0')
	{
		if (letter == wordLetter[pointer])
		{
			return true;
		}

		pointer++;
	}

	return false;
}

/// <summary>
/// Determine if the line contains any GCode words.
/// </summary>
/// <returns>True if there are no words.</returns>
/// <remarks>Words are not validated.<remark>
bool GcodeParser_NoWords()
{
	if (GcodeParser_line[0] == '\0' || GcodeParser_blockDelete || GcodeParser_beginEnd)
	{
		return true;
	}

	int pointer = 0;
	while (wordLetter[pointer] != '\0')
	{
		if (GcodeParser_HasWord(wordLetter[pointer]))
		{
			return false;
		}

		pointer++;
	}

	return true;
}

/// <summary>
/// Gets the value following the word.
/// </summary>
/// <param name="letter">The letter of the word to look for in the line.</param>
/// <returns>The value following the letter for the word.</returns>
/// <remarks>
/// Currently the parser is not sophisticated enough to deal with parameters, 
/// Boolean operators, expressions, binary operators, functions and repeated items.
/// </remarks>
double GcodeParser_GetWordValue_float(char letter)
{
	int pointer = GcodeParser_FindWord(letter);

	if (GcodeParser_line[pointer] != '\0')
		return (double)strtod(&GcodeParser_line[pointer + 1], NULL);

	return 0.0;
}

int GcodeParser_GetWordValue_int(char letter)
{
	int pointer = GcodeParser_FindWord(letter);

	if (GcodeParser_line[pointer] != '\0')
		return (int)strtol(&GcodeParser_line[pointer + 1], NULL, 10); //The last one is Base, 10 for Decimal, 16 of Hexadecimal.

	return 0;
}

void GcodeParser_Execute(){
	GcodeParser_ParseLine();
	GcodeParser_RemoveCommentSeparators();
	//Check command completeness by checking keyword 'E'. If the command is incomplete, reject the command
	bool completeness_command = GcodeParser_HasWord('E');
	if (completeness_command){
		//Reject the current command
		int param_m = GcodeParser_GetWordValue_int('M');
		switch (param_m)
		{
			case 120:
				M120();
				break;
	
			case 121:
				M121();
				break;
	
			case 122:
				M122();
				break;
	
			case 123:
				M123();
				break;
	
			case 124:
				M124();
				break;
	
			case 125:
				M125();
				break;
	
			case 126:
				M126();
				break;
	
			case 127:
				M127();
				break;
			
			case 128:
				M128();
				break;
	
			case 129:
				M129();
				break;
	
			case 130:
				M130();
				break;
			
			case 131:
				M131();
				break;
			
			case 140:
				M140();
				break;
	
			case 150:
				M150();
				break;
			
			case 170:
				M170();
				break;
	
			case 171:
				M171();
				break;
	
			case 172:
				M172();
				break;
			
			case 173:
				M173();
				break;
			
			case 174:
				M174();
				break;
	
			case 175:
				M175();
				break;
			
			case 176:
				M176();
				break;
	
			case 177:
				M177();
				break;
	
			case 178:
				M178();
				break;
			
			case 179:
				M179();
				break;

			case 180:
				M180();
				break;

			case 181:
				M181();
				break;

			case 182:
				M182();
				break;
				
			default:
				printf("Unknown Gcode command\n");
				break;
		}
	} else {
		printf("Command needs to end with character 'E'\n");
	}
	GcodeParser_Initialize(); 
}
