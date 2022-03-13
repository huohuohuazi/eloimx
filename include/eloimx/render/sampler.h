/*
    sampler.h
    create: 2022.2.25
*/

#pragma once
#include <eloimx/eloimx.h>

ELX_NAMESPACE_BEGIN

class elxSampler {
public:
    float sample1D() const;
    Point2f sample2D() const;

};

ELX_NAMESPACE_END