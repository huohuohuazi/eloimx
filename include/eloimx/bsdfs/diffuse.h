#pragma once
#include <eloimx/eloimx.h>
#include <eloimx/render/bsdf.h>

ELX_NAMESPACE_BEGIN
class elxDiffuse : public elxBSDF {
    // hack, should be texture
    elxSpectrum color;
    
    elxDiffuse() { }
public:
    elxDiffuse(const elxSpectrum &spc) : color(spc) { }

    virtual elxSpectrum sample(elxBSDFSamplingRecord &bRec, const Point2f &sample) const;

    virtual elxSpectrum sample(elxBSDFSamplingRecord &bRec, const Point2f &sample, float &pdf) const;

    virtual elxSpectrum eval(const elxBSDFSamplingRecord &bRec) const;

    virtual float pdf(const elxBSDFSamplingRecord &bRec) const;

    virtual std::string toString() const;
};
ELX_NAMESPACE_END