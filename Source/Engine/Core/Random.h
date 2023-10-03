#pragma once
#include <random>

namespace nc
{
	inline void seedRandom(unsigned int seed) { srand(seed); }
	
	// Integer random functions

	// Returns an integer between 0 and RAND_MAX (0x7fff)
	inline int random() { return rand(); }
	// Returns an integer between 0 and max - 1
	inline int random(unsigned int max) { return rand() % max; }
	// Returns an integer between min and max
	inline int random(unsigned int min, unsigned int max) { return min + random((max - min) + 1); } // min - max

	// Floating-Point random functions

	// Returns a float between 0 and 1.0
	inline float randomf() { return random() / (float)RAND_MAX; }
	// Returns a float between 0 and max
	inline float randomf(float max) { return randomf() * max; }
	// Returns a float between min and max
	inline float randomf(float min, float max) { return min + randomf() * (max - min); }
}
