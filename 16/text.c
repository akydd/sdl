/*
 * =====================================================================================
 *
 *       Filename:  text.c
 *
 *    Description:  Implementation of text component functions
 *
 *        Version:  1.0
 *        Created:  14-05-16 11:10:17 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alan Kydd
 *
 * =====================================================================================
 */
#include <stdlib.h>

#include "text.h"

void set_text(struct text *text, char *string)
{
    if (text->text != NULL) {
        free(text->text);
    }

    text->text = (char *)malloc(sizeof(char) * (strlen(string) + 1));
    (void)strcpy(text->text, string);
}
