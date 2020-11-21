#include "MathUtils.hpp"
#include <glm/gtx/random.hpp>

float MathUtils::rand(float min, float max)
{
	return glm::linearRand(min, max);
}

float MathUtils::min(float a, float b)
{
    return a < b ? a : b;
}