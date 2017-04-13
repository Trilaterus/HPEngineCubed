/*
A namepsace of helpful math related functions
*/

#pragma once

#include <algorithm>

namespace Maths
{
	int Clamp(int iValue, int iMin, int iMax)
	{
		// http://stackoverflow.com/a/9324086
		return std::max(iMin, std::min(iValue, iMax));
	}
}