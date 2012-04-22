/*
 * newarray.h
 *
 *  Created on: 22 avr. 2012
 *      Author: Koudja
 */

#ifndef NEWARRAY_H_
#define NEWARRAY_H_

#include <new.h>

void * operator new(size_t size);
void operator delete(void * ptr);

#endif /* NEWARRAY_H_ */
