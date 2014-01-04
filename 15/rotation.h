/*
 * =====================================================================================
 *
 *       Filename:  rotation.h
 *
 *    Description:  Definition of the rotation component
 *
 *        Version:  1.0
 *        Created:  14-01-03 08:47:07 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alan Kydd
 *
 * =====================================================================================
 */

#ifndef ROTATION_H
#define ROTATION_H

typedef struct {
	double angle;
	// these two set the coordinate point around which the rotation is performed
	int x;
	int y;
	// 0 = none, 1 = horizontal, 2 = vertical
	int flip;
} rotation;

#endif
