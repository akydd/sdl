/*
 * =====================================================================================
 *
 *       Filename:  input_system.h
 *
 *    Description:  Input system for the Entity Component Manager.  It does not
 *    hold state, but is simply a collection of functions.
 *
 *        Version:  1.0
 *        Created:  13-12-01 08:45:48 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alan Kydd
 *
 * =====================================================================================
 */
#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

extern void input_system_update(SDL_Event, world *);

#endif
