/*
 * =====================================================================================
 *
 *       Filename:  text.h
 *
 *    Description:  Definition of the text component
 *
 *        Version:  1.0
 *        Created:  14-01-04 10:18:22 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alan Kydd
 *
 * =====================================================================================
 */

#ifndef TEXT_H
#define TEXT_H

typedef struct {
	char *font;
	char *text;
	int size;
	// Style: 0 = normal, 1 = bold, 2 = italic, 4 = underline, 8 = strikethrough.
	// The last 4 can be combined using bitwise OR.  ORing normal with any other
	// style will override.
	int style;
} text;

#endif
