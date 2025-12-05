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

// #ifndef GCodeParser_h
// #define GCodeParser_h
#pragma once
#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <printf_custom/printf.h>

#ifndef GCODEPARSER_h
#define GCODEAPRSER_h

#define GCODEPARSER_MAX_LINE_SIZE 256 // Maximun GCode line size.

/// <summary>
/// The GCodeParser library is a lightweight G-Code parser for the Arduino using only
/// a single character buffer to first collect a line of code (also called a 'block') 
/// from a serial or file input and then parse that line into a code block and comments.
/// 
/// The parser was originally designed for use with code for the SphereBot, an EggBot clone.
/// 
/// Limitations
/// Currently the parser is not sophisticated enough to deal with parameters, Boolean
/// operators, expressions, binary operators, functions and repeated items. However, 
/// this should not be an obstacle when building 2D/3D plotters, CNC, and projects with 
/// an Arduino controller.
///
/// References
/// The following are just a few sources of information on GCode.
/// https://www.autodesk.com/products/fusion-360/blog/cnc-programming-fundamentals-g-code/
/// http://www.machinekit.io/docs/gcode/overview/
/// https://www.reprap.org/wiki/G-code
/// https://howtomechatronics.com/tutorials/g-code-explained-list-of-most-important-g-code-commands/ 
/// </summary>
// class GCodeParser
// {
// private:
//	int GcodeParser_lineCharCount;
//	char GcodeParser_line[GCODEPARSER_MAX_LINE_SIZE + 2];
//	char* GcodeParser_comments;
//	char* GcodeParser_lastComment;
//	bool GcodeParser_blockDelete;
//	bool GcodeParser_beginEnd;
//	bool GcodeParser_completeLineIsAvailableToParse;

	// GCodeParser();
	bool GcodeParser_AddCharToLine(char c);
	void GcodeParser_Initialize();
	void GcodeParser_ParseLine();
	void GcodeParser_ParseLine_char(char* gCode);
	void GcodeParser_RemoveCommentSeparators();

	bool GcodeParser_HasWord(char letter);
	int GcodeParser_FindWord(char letter);
	bool GcodeParser_IsWord(char letter);
	bool GcodeParser_NoWords();

	double GcodeParser_GetWordValue_float(char letter);
	int GcodeParser_GetWordValue_int(char letter);

	void GcodeParser_Execute();
// };
#endif //GCODEPARSER_h