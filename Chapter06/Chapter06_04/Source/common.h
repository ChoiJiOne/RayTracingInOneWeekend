#pragma once

#include <cmath>
#include <limits>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degree_to_radians(double degree)
{
	return degree * pi / 180.0;
}