#include <iostream>
#include "Core/Random.h"
#include "Core/FileIO.h"
#include "Core/Memory.h"

using namespace std;



int main()
{
	
	int* p = new int;
	delete p;

	cout << kiko::getFilePath() << endl;
	kiko::setFilePath("Assets");
	cout << kiko::getFilePath() << endl;
	size_t size = 0;
	kiko::getFileSize("game.txt", size);
	cout << size << endl;

	std::string s;
	kiko::readFile("game.txt", s);
	cout << s << endl;

	kiko::seedRandom((unsigned int)time(nullptr));
	for (int i = 0; i < 10; i++)
	{
		cout << kiko::random(20) % 100 << endl;
	}
	
}

/* - Random.h -

	#pragma once
	#include <random>

	namespace kiko
	{
		void seedRandom(unsigned int) { srand(seed); }
		int random() { return rand(); }
		int random(unsigned int max) { return rand() % max; } // 0 - (max - 1)
		int random(unsigned int min, unsigned int max) { return min + random((max - min) + 1); } // min - max
	}
*/

/* - FileIO.h - 
#pragma once
#include <filesystem>
#include <string>

	std::string getFilePath();
	bool setFilePath(const std::filesystem::path& path);

	bool fileExists(const std::filesystem::path& path);
	bool getFileSize(const std::filesystem::path& path, size_t& size);
	bool readFile(const std::filesystem::path& path, std::string buffer);

	// Highlight bool lines and use Alt+Enter to add required definitions

*/

/* - FileIO.cpp -
#include "fileIO.h"
#include <fstream>

namespace kiko
{
	std::string kiko::getFilePath()
	{
		return std::filesystem::current_path().string();
	}

	// For setFilePath...

	std::error_code ec;
	std::filesystem::current_path(path, ec);

	return ec.value() == 0;

	// For fileExists...

	return std::filesystem::exists(path);

	// For getFileSize...

	std::error_code ec;
	size = std::filesystem::file_size(path, ec);

	return ec.value() == 0;

	// For readFile...

	if (!fileExists(path)) return false;

	size_t size;
	if (!getFileSize(path, size)) return false;

	buffer.resize(size);

	std::ifstream stream(path);
	stream.read(buffer.data(), size);
	stream.close();

	return true;
}
*/

/* - Memory.h -
#pragma once

namespace kiko
{
	struct MemoryAllocation
	{
		void* address;
		size_t size;
		MemoryAllocation* next;
	};

	class MemoryTracker
	{
	public:
		//void Add(void* address, size_t size);
		//void Remove(void* address);

	private:



	}
}
*/

/* - Memory.cpp -
#include "Memory.h"
#include <iostream>

using namespace std;

void* operator new (size_t size)
{
	cout << "Allocated: " << size << endl;
	return malloc(size);
}

void operator delete (void* address, size_t size)
{
	cout << "Deallocated: " << size << endl;

	free(address);
}
*/