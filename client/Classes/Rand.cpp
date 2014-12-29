#include "Rand.h"
#include <random>

static std::mt19937 generator;
static std::uniform_real_distribution<float> distribution(0, 1);

float Rand::get()
{
	return distribution(generator);
}
