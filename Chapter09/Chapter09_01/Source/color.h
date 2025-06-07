#pragma once

#include "vec3.h"
#include "interval.h"

using color = vec3;

inline void write_color(std::ostream& out, const color& pixel_color)
{
	double r = pixel_color.x();
	double g = pixel_color.y();
	double b = pixel_color.z();

	static const interval intensity(0.000, 0.999);

	int rbyte = static_cast<int>(256.0 * intensity.clamp(r));
	int gbyte = static_cast<int>(256.0 * intensity.clamp(g));
	int bbyte = static_cast<int>(256.0 * intensity.clamp(b));

	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
