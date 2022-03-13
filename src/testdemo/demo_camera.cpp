#include <eloimx/eloimx.h>
#include <eloimx/render/perspective.h>

void test() {
    using namespace eloimx;
    elxPerspectiveCamera camera;
    elxRay ray;

    camera.generateRay(ray, Point2f(1.0, 1.0));
    std::cout << ray.toString() << "\n";

    camera.generateRay(ray, Point2f(0.5, 1.0));
    std::cout << ray.toString() << "\n";

    camera.generateRay(ray, Point2f(1.0, 0.5));
    std::cout << ray.toString() << "\n";

    camera.generateRay(ray, Point2f(0.5, 0.5));
    std::cout << ray.toString() << "\n";

    camera.generateRay(ray, Point2f(0, 0));
    std::cout << ray.toString() << "\n";

}
