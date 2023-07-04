#include "Memory.h"
#include <iostream>

using namespace std;
kiko::MemoryTracker kiko::g_memoryTracker;

void* operator new (size_t size)
{
	void* p = malloc(size);

	kiko::g_memoryTracker.Add(p, size);

	return p;
}

void operator delete (void* address, size_t size)
{
	kiko::g_memoryTracker.Remove(address ,size);
	free(address);
}

namespace kiko
{
	void MemoryTracker::Add(void* address, size_t size)
	{
		n_bytesAllocated += size;
		n_numAllocations++;
	}
	void MemoryTracker::Remove(void* address, size_t size)
	{
		n_bytesAllocated -= size;
		n_numAllocations--;
	}
	void MemoryTracker::DisplayInfo()
	{
		cout << "Current Bytes Allocated: " << n_bytesAllocated << endl;
		cout << "Current Number Allocations: " << n_numAllocations << endl;
	}
}
