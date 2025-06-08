#pragma once

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable
{
public:
	sphere(const point3& center, double radius, std::shared_ptr<material> material) 
		: _center(center), _radius(std::fmax(0.0, radius)), _material(material) {}

	bool hit(const ray& r, interval ray_t, hit_record& record) const override
	{
		vec3 oc = _center - r.origin();
		double a = r.direction().length_squared();
		double h = dot(r.direction(), oc);
		double c = oc.length_squared() - _radius * _radius;

		double discriminant = h * h - a * c;
		if (discriminant < 0.0)
		{
			return false;
		}

		double sqrtd = std::sqrt(discriminant);
		double root = (h - sqrtd) / a;
		if (!ray_t.surrounds(root))
		{
			root = (h + sqrtd) / a;
			if (!ray_t.surrounds(root))
			{
				return false;
			}
		}

		record.t = root;
		record.p = r.at(record.t);

		vec3 outward_normal = (record.p - _center) / _radius;
		record.set_face_normal(r, outward_normal);

		record.mat = _material;

		return true;
	}

private:
	point3 _center;
	double _radius;
	std::shared_ptr<material> _material;
};