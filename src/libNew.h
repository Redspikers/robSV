//New pour les tableaux

#ifndef LIBNEW_H
#define LIBNEW_H

#include <stdlib.h>

void * operator new(size_t size);
void operator delete(void * ptr);
void * operator new[](size_t size);
void operator delete[](void * ptr);
#endif
