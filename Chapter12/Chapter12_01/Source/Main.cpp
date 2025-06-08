#include "camera.h"
#include "color.h"
#include "common.h"
#include "hittable.h"
#include "hittable_list.h"
#include "ray.h"
#include "sphere.h"
#include "vec3.h"

int main(void)
{
	std::shared_ptr<lambertian> material_left = std::make_shared<lambertian>(color(0.0, 0.0, 1.0));
	std::shared_ptr<lambertian> material_right = std::make_shared<lambertian>(color(1.0, 0.0, 0.0));

	hittable_list world;
	auto radius = std::cos(pi / 4.0);
	world.add(std::make_shared<sphere>(point3(-radius, 0, -1), radius, material_left));
	world.add(std::make_shared<sphere>(point3(+radius, 0, -1), radius, material_right));

	camera cam;
	cam.render(world);

	return 0;
}