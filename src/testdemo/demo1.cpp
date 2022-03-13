#include <glm/glm.hpp>
#include <iostream>

void test() {
    glm::vec3 v1(1, 2, 3), v2(5, 6, 7);
    glm::vec3 res = v1 + v2;
    std::cout << res.x << " " << res.y << " " << res.z <<"\n";
}