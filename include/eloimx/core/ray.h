/*
    ray.h
    create: 2022.2.23
*/

#pragma once

#include <eloimx/eloimx.h>
#include <embree3/rtcore_ray.h>
#include <fmt/format.h>

ELX_NAMESPACE_BEGIN
class elxRay {
public:
    //RTCRay ray;
    Point3f o;
    Vec3f d;
    float tfar, tnear, time;
public:
    elxRay();

    elxRay(const Point3f &org, const Vec3f &dir);

    elxRay(const Point3f &o, const Vec3f &d, float tmin, float tmax);

    Point3f operator()(float t) const;

    std::string toString() const;

    RTCRay toRTC() const;
};
ELX_NAMESPACE_END