/*
 * =====================================================================================
 *
 *       Filename:  table.c
 *
 *    Description:  Table implementation
 *
 *        Version:  1.0
 *        Created:  13-11-29 09:24:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alan Kydd
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <string.h>

#include "table.h"

struct table {
	char *key;
	void *value;
	struct table *next;
};

table *table_new() 
{
	return NULL;
}

void table_free(table **table)
{
	while(*table != NULL) {
		table *entry = *table;
		*table = entry->next;
		free(entry);
	}
}

void *table_get(table *table, const char *key)
{
	for(table *p = table; p; p = p->next) {
		if(strcmp(key, p->key) == 0) {
			return p->value;
		}
	}
	return NULL;
}

void table_put(table **table, const char *key, void *value)
{
	// Search table for key
	for(table *p = *table; p; p = p->next) {
		if(strcmp(key, p->key) == 0) {
			p->value = value;
			return;
		}
	}

	// create new element
	table *new_table = malloc(sizeof(table));
	new_table->key = malloc(sizeof(char) * (strlen(key) + 1));
	(void)strcpy(new_table->key, key);
	new_table->value = value;

	// insert new element at front of list
	new_table->next = *table;
	*table = new_table;
	return;
}

void *table_remove(table **table, const char *key)
{
	table **p = table;
	while(*p != NULL) {
		if (strcmp((*p)->key, key) == 0) {
			table *delete = *p;
			*p = delete->next;
			free(delete);
		} else {
			p = &(*p)->next;
		}
	}
}
