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
	hittable_list world;
	world.add(std::make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5));
	world.add(std::make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0));

	camera cam;
	cam.render(world);

	return 0;
}