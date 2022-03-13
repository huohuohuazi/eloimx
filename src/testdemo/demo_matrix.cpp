#include <glm/glm.hpp>
#include <eloimx/eloimx.h>
void test() {
    eloimx::elxFrame frame(Vec3f(6,1,9));

    Vec3f local = frame.toLocal(Vec3f(6, 1, 6));

    std::cout<<local.x<<" "<<local.y<<" "<<local.z<<"\n";

    Vec3f world = frame.toWorld(local);

    std::cout<<world.x<<" "<<world.y<<" "<<world.z<<"\n";

    std::cout<<frame.toString()<<"\n";

}