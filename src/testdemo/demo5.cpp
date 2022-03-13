#include <glm/gtc/random.hpp>
#include <iostream>
void test(){
    for (int i = 0; i < 10; ++i)
        std::cout << glm::linearRand(.0f, 1.0f) << "\n";
}