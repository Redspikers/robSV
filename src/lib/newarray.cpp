/*
 * newarray.cpp
 *
 *  Created on: 22 avr. 2012
 *      Author: Koudja
 */

#include "newarray.h"

void * operator new[](size_t size) {
	return malloc(size);
}

void operator delete[](void * ptr) {
	free(ptr);
}
