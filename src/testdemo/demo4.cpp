#include <eloimx/core/ray.h>

void test() {
    eloimx::elxRay ray(Point3f(0,0,0), Vec3f(1.0, 2.0, 3.0));
    std::cout << ray.toString();
}