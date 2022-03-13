#pragma once
#include <eloimx/eloimx.h>

ELX_NAMESPACE_BEGIN

class elxRenderJob {
    std::string imageName;
    char *color;

    elxRenderJob() { };
public:
    unsigned height, width;
    unsigned spp;

    elxRenderJob(std::string imgName, unsigned height, unsigned width, unsigned spp):
        imageName(imgName), height(height), width(width), spp(spp){
        color = new char[height * width * 3];
    }

    ~elxRenderJob() {
        delete color;
    }

    inline void setPixel(unsigned x, unsigned y, const elxSpectrum &spc) {
        color[x * 3 + y * width * 3]     = (char) (spc.r * 255);
        color[x * 3 + y * width * 3 + 1] = (char) (spc.g * 255);
        color[x * 3 + y * width * 3 + 2] = (char) (spc.b * 255);
    }    

    void writeTga() const;
};

ELX_NAMESPACE_END