#pragma once

#include <eloimx/eloimx.h>
ELX_NAMESPACE_BEGIN
namespace warp {

    float squareToCosHemispherePdf(const Vec3f &d);

    Vec3f squareToCosHemisphere(const Point2f &sample);

    Point2f squareToUniformDiskConcentric(const Point2f &sample);
};
ELX_NAMESPACE_END