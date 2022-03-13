#pragma once
#include <eloimx/eloimx.h>
#include <eloimx/render/intersection.h>

ELX_NAMESPACE_BEGIN
class elxEmitter {
    friend class Shape;
protected:
    elxEmitter(){ }
    Shape *m_shape;
public:
    virtual elxSpectrum eval(const elxIntersection &its, const Vec3f &d) const=0;
    virtual elxSpectrum sampleDirect(elxDirectSamplingRecord &dRec, const Point2f &sample) const=0;
    virtual std::string toString() const=0;
};

class elxAreaLight : public elxEmitter {
protected:
    // hack, constant now
    elxSpectrum m_emission;
public:
    elxAreaLight(const elxSpectrum &spc):m_emission(spc) {
        m_shape = nullptr;
    }

    virtual elxSpectrum eval(const elxIntersection &its, const Vec3f &d) const;

    virtual elxSpectrum sampleDirect(elxDirectSamplingRecord &dRec, const Point2f &sample) const;

    virtual std::string toString() const;
};
ELX_NAMESPACE_END