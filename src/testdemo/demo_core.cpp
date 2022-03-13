#include <eloimx/core/math.h>

void test() {
    Vec3f v(1.0, 1.0, 1.0);
    normalize(v);
    std::cout << fmt::format("v=[{}, {}, {}]",v.x, v.y, v.z);
}