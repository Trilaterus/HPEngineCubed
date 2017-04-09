#include "RandomResource.h"

namespace RandomResource
{
	int generateInt(int iMin, int iMax)
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> dist(iMin, iMax);
		return dist(mt);
	}

	float generateFloat(float fMin, float fMax)
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<float> dist(fMin, fMax);
		return dist(mt);
	}

	bool generateBool()
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> dist(0, 100);
		if (dist(mt) <= 50)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}