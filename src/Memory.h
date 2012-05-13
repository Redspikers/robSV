#ifndef __MEMORY__
#define __MEMORY__

#include <Arduino.h>

class Memory {
	public:
		int freeMemory();
		int freeListSize();

};

#endif
