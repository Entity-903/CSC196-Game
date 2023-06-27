#include <iostream>
#include "../../Engine/Core/Random.h" // Core/Random.h
#include "../../Engine/Core/FileIO.h" // Core/FileIO.h

using namespace std;

int main()
{
	cout << kiko::getFilePath() << endl;


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


*/

/* - FileIO.cpp -
#include "fileIO.h"

namespace kiko
{
	std::string kiko::getFilePath()
	{
		return std::filesystem::current_path().string();
	}

}
*/