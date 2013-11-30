/*
 * =====================================================================================
 *
 *       Filename:  table.h
 *
 *    Description:  table - a set of key-value pairs, where keys are
 *    unique strings.
 *
 *        Version:  1.0
 *        Created:  13-11-29 08:45:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alan Kydd
 *
 * =====================================================================================
 */

#ifndef TABLE_H
#define TABLE_H

typedef struct table table;

extern table *table_new();
extern void table_free(table **table);
extern void *table_get(table *table, const char *key);
extern void table_put(table **table, const char *key, void *value);
extern void *table_remove(table **table, const char *key);

#endif
