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
				color pixel_color(0.0, 0.0, 0.0);
				for (int sample = 0; sample < _samples_per_pixel; ++sample)
				{
					ray r = get_ray(i, j);
					pixel_color += ray_color(r, _max_depth, world);
				}
				write_color(std::cout, _pixel_samples_scale * pixel_color);
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

		_pixel_samples_scale = 1.0 / _samples_per_pixel;

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

	ray get_ray(int i, int j) const
	{
		vec3 offset = sample_square();
		vec3 pixel_sample = _pixel00_loc + ((i + offset.x()) * _pixel_delta_u) + ((j + offset.y()) * _pixel_delta_v);

		vec3 ray_origin = _center;
		vec3 ray_direction = pixel_sample - ray_origin;

		return ray(ray_origin, ray_direction);
	}

	vec3 sample_square() const
	{
		return vec3(random_double() - 0.5, random_double() - 0.5, 0.0);
	}

	color ray_color(const ray& r, int depth, const hittable& world) const
	{
		if (depth <= 0)
		{
			return color(0.0, 0.0, 0.0);
		}

		hit_record record;
		if (world.hit(r, interval(0.001, infinity), record))
		{
			vec3 direction = random_on_hemisphere(record.normal);
			return 0.5 * ray_color(ray(record.p, direction), depth - 1, world);
		}

		vec3 unit_direction = unit_vector(r.direction());
		double a = 0.5 * (unit_direction.y() + 1.0f);
		return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
	}

private:
	double _aspect_ratio = 1.0;
	int _image_width = 100;
	int _image_height = 0;
	int _samples_per_pixel = 100;
	double _pixel_samples_scale = 0.0;
	int _max_depth = 50;
	point3 _center;
	point3 _pixel00_loc;
	vec3 _pixel_delta_u;
	vec3 _pixel_delta_v;
};