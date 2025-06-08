#pragma once

#include "color.h"
#include "hittable.h"
#include "material.h"

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
		_lookfrom = point3(13.0, 2.0, 3.0);
		_lookat = point3(0.0, 0.0, 0.0);
		_vup = vec3(0.0, 1.0, 0.0);
		_defocus_angle = 0.6;
		_focus_dist = 10.0;
		
		_aspect_ratio = 16.0 / 9.0;
		_image_width = 1200;
		_image_height = static_cast<int>(static_cast<double>(_image_width) / _aspect_ratio);
		_image_height = std::max(1, _image_height);
		_samples_per_pixel = 500;

		_pixel_samples_scale = 1.0 / _samples_per_pixel;

		_center = _lookfrom;

		double theta = degree_to_radians(_vfov);
		double h = std::tan(theta / 2.0);
		double viewport_height = 2.0 * h * _focus_dist;
		double viewport_width = viewport_height * (static_cast<double>(_image_width) / static_cast<double>(_image_height));
		
		_w = unit_vector(_lookfrom - _lookat);
		_u = unit_vector(cross(_vup, _w));
		_v = cross(_w, _u);

		vec3 viewport_u = viewport_width * _u;
		vec3 viewport_v = viewport_height * -_v;
		_pixel_delta_u = viewport_u / static_cast<double>(_image_width);
		_pixel_delta_v = viewport_v / static_cast<double>(_image_height);

		vec3 viewport_upper_left = _center - (_focus_dist * _w) - viewport_u / 2.0 - viewport_v / 2.0;
		_pixel00_loc = viewport_upper_left + 0.5 * (_pixel_delta_u + _pixel_delta_v);

		double defocus_radius = _focus_dist * std::tan(degree_to_radians(_defocus_angle / 2.0));
		_defocus_disk_u = _u * defocus_radius;
		_defocus_disk_v = _v * defocus_radius;
	}

	ray get_ray(int i, int j) const
	{
		vec3 offset = sample_square();
		vec3 pixel_sample = _pixel00_loc + ((i + offset.x()) * _pixel_delta_u) + ((j + offset.y()) * _pixel_delta_v);

		vec3 ray_origin = (_defocus_angle <= 0.0) ? _center : defocus_disk_sample();
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
			ray scattered;
			color attenuation;

			if (record.mat->scatter(r, record, attenuation, scattered))
			{
				return attenuation * ray_color(scattered, depth - 1, world);
			}

			return color(0.0, 0.0, 0.0);
		}

		vec3 unit_direction = unit_vector(r.direction());
		double a = 0.5 * (unit_direction.y() + 1.0f);
		return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
	}

	point3 defocus_disk_sample() const
	{
		vec3 p = random_in_unit_disk();
		return _center + (p[0] * _defocus_disk_u) + (p[1] * _defocus_disk_v);
	}

private:
	double _aspect_ratio = 1.0;
	int _image_width = 100;
	int _image_height = 0;
	int _samples_per_pixel = 100;
	double _pixel_samples_scale = 0.0;
	int _max_depth = 50;
	
	double _vfov = 20.0;
	point3 _lookfrom = point3(0.0, 0.0, 0.0);
	point3 _lookat = point3(0.0, 0.0, -1.0);
	vec3 _vup = vec3(0.0, 1.0, 0.0);
	vec3 _u;
	vec3 _v;
	vec3 _w;

	double _defocus_angle = 0.0;
	double _focus_dist = 10.0;
	vec3 _defocus_disk_u;
	vec3 _defocus_disk_v;

	point3 _center;
	point3 _pixel00_loc;
	vec3 _pixel_delta_u;
	vec3 _pixel_delta_v;
};