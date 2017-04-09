/*
A namespace of helper functions to generate random
types such as ints, floats and bools.
*/

#pragma once

#include <random>

namespace RandomResource
{
	int generateInt(int iMin, int iMax);

	float generateFloat(float fMin, float fMax);

	bool generateBool();
}