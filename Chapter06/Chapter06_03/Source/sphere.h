#pragma once

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable
{
public:
	sphere(const point3& center, double radius) 
		: _center(center), _radius(radius) {}

	bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& record) const override
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
		if (root <= ray_tmin || root >= ray_tmax)
		{
			root = (h + sqrtd) / a;
			if (root <= ray_tmin || root >= ray_tmax)
			{
				return false;
			}
		}

		record.t = root;
		record.p = r.at(record.t);

		vec3 outward_normal = (record.p - _center) / _radius;
		record.set_face_normal(r, outward_normal);

		return true;
	}

private:
	point3 _center;
	double _radius;
};