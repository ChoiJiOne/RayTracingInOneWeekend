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
	std::shared_ptr<lambertian> material_ground = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
	std::shared_ptr<lambertian> material_center = std::make_shared<lambertian>(color(0.1, 0.2, 0.5));
	std::shared_ptr<dielectric> material_left = std::make_shared<dielectric>(1.00 / 1.33);
	std::shared_ptr<metal> material_right = std::make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

	hittable_list world;
	world.add(std::make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(std::make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));
	world.add(std::make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
	world.add(std::make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

	camera cam;
	cam.render(world);

	return 0;
}