#pragma once

#include "hittable.h"

#include <memory>
#include <vector>

class hittable_list : public hittable
{
public:
	hittable_list() {}
	void clear() { _objects.clear(); }
	void add(std::shared_ptr<hittable> object)
	{
		_objects.push_back(object);
	}

	bool hit(const ray& r, interval ray_t, hit_record& rec) const override
	{
		hit_record record;
		bool hit_anything = false;
		double closest_so_far = ray_t.max();

		for (const auto& object : _objects)
		{
			if (object->hit(r, interval(ray_t.min(), closest_so_far), record))
			{
				hit_anything = true;
				closest_so_far = record.t;
				rec = record;
			}
		}

		return hit_anything;
	}

private:
	std::vector<std::shared_ptr<hittable>> _objects;
};