#include "Utility.h"

#include <random>
#include <ctime>

namespace
{
	std::default_random_engine createRandomEngine()
	{
		auto seed = static_cast<unsigned long>(std::time(nullptr));
		return std::default_random_engine(seed);
	}

	auto RandomEngine = createRandomEngine();
}

int randomInt(int exclusiveMax)
{
	std::uniform_int_distribution<> distr(0, exclusiveMax - 1);
	return distr(RandomEngine);
}
