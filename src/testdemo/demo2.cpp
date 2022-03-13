#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

void test() {
    char color[100 * 100 * 3];
    for (int i = 0; i < 100 * 100 * 3; ++i)
        color[i] = 100;
    stbi_write_tga("demo2.tga", 100, 100, 3, color);
}