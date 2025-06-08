#pragma once

#include "vec3.h"
#include "interval.h"

using color = vec3;

inline double linear_to_gamma(double linear_component)
{
	if (linear_component > 0.0)
	{
		return std::sqrt(linear_component);
	}

	return 0.0;
}

inline void write_color(std::ostream& out, const color& pixel_color)
{
	double r = linear_to_gamma(pixel_color.x());
	double g = linear_to_gamma(pixel_color.y());
	double b = linear_to_gamma(pixel_color.z());

	static const interval intensity(0.000, 0.999);

	int rbyte = static_cast<int>(256.0 * intensity.clamp(r));
	int gbyte = static_cast<int>(256.0 * intensity.clamp(g));
	int bbyte = static_cast<int>(256.0 * intensity.clamp(b));

	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
