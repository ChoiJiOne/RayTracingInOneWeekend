#pragma once

#include "color.h"
#include "hittable.h"

class material
{
public:
	virtual ~material() = default;

	virtual bool scatter(const ray& r_in, const hit_record& record, color& attenuation, ray& scattered) const
	{
		return false;
	}
};

class lambertian : public material
{
public:
	lambertian(const  color& albedo) : _albedo(albedo) {}

	virtual bool scatter(const ray& r_in, const hit_record& record, color& attenuation, ray& scattered) const override
	{
		vec3 scatter_direction = record.normal + random_unit_vector();

		if (scatter_direction.near_zero())
		{
			scatter_direction = record.normal;
		}

		scattered = ray(record.p, scatter_direction);
		attenuation = _albedo;
		return true;
	}

private:
	color _albedo;
};

class metal : public material
{
public:
	metal(const color& albedo, double fuzz) : _albedo(albedo), _fuzz(fuzz) {}

	virtual bool scatter(const ray& r_in, const hit_record& record, color& attenuation, ray& scattered) const override
	{
		vec3 reflected = reflect(r_in.direction(), record.normal);
		reflected = unit_vector(reflected) + (_fuzz * random_unit_vector());

		scattered = ray(record.p, reflected);
		attenuation = _albedo;

		return dot(scattered.direction(), record.normal) > 0.0;
	}

private:
	color _albedo;
	double _fuzz = 0.0;
};