#pragma once
#include <eloimx/eloimx.h>
#include <eloimx/render/intersection.h>

ELX_NAMESPACE_BEGIN
struct elxDirectSamplingRecord {
/*--------------- ref field ---------------------*/
    /// the point for direct sampling
    Point3f ref;

    /// normal of the point
    Vec3f refN;

    /// unit direction from the reference point to the target direction
    Vec3f d;

    /// the distance
    float dist;

/*--------------- point field ---------------------*/
    Point3f p;

    Vec3f n;

    float pdf;

    elxDirectSamplingRecord() { }

    elxDirectSamplingRecord(const elxIntersection &its);

    std::string toString() const;


};
ELX_NAMESPACE_END