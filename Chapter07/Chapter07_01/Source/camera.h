#pragma once

#include "color.h"
#include "hittable.h"

class camera
{
public:
	camera()
	{
		initialize();
	}

	void render(const hittable& world)
	{
		std::cout << "P3\n" << _image_width << ' ' << _image_height << "\n255\n";

		for (int j = 0; j < _image_height; ++j)
		{
			std::clog << "\rScanlines remaining: " << (_image_height - j) << ' ' << std::flush;
			for (int i = 0; i < _image_width; ++i)
			{
				vec3 pixel_center = _pixel00_loc + (static_cast<double>(i) * _pixel_delta_u + static_cast<double>(j) * _pixel_delta_v);
				vec3 ray_direction = pixel_center - _center;

				ray r(_center, ray_direction);

				color pixel_color = ray_color(r, world);
				write_color(std::cout, pixel_color);
			}
		}

		std::clog << "\rDone.                 \n";
	}

private:
	void initialize()
	{
		_aspect_ratio = 16.0 / 9.0;
		_image_width = 400;
		_image_height = static_cast<int>(static_cast<double>(_image_width) / _aspect_ratio);
		_image_height = std::max(1, _image_height);

		double focal_length = 1.0;
		double viewport_height = 2.0f;
		double viewport_width = viewport_height * (static_cast<double>(_image_width) / static_cast<double>(_image_height));
		_center = point3(0.0, 0.0, 0.0);

		vec3 viewport_u = vec3(viewport_width, 0.0, 0.0);
		vec3 viewport_v = vec3(0.0, -viewport_height, 0.0);
		_pixel_delta_u = viewport_u / static_cast<double>(_image_width);
		_pixel_delta_v = viewport_v / static_cast<double>(_image_height);

		vec3 viewport_upper_left = _center - vec3(0.0, 0.0, focal_length) - viewport_u / 2.0 - viewport_v / 2.0;
		_pixel00_loc = viewport_upper_left + 0.5 * (_pixel_delta_u + _pixel_delta_v);
	}

	color ray_color(const ray& r, const hittable& world) const
	{
		hit_record record;
		if (world.hit(r, interval(0.0, infinity), record))
		{
			return 0.5 * (record.normal + color(1.0, 1.0, 1.0));
		}

		vec3 unit_direction = unit_vector(r.direction());
		double a = 0.5 * (unit_direction.y() + 1.0f);
		return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
	}

private:
	double _aspect_ratio = 1.0;
	int _image_width = 100;
	int _image_height = 0;
	point3 _center;
	point3 _pixel00_loc;
	vec3 _pixel_delta_u;
	vec3 _pixel_delta_v;
};