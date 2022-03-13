/*
    an implimentation of sensor
    create: 2022.2.24
*/
#pragma once

#include <eloimx/render/sensor.h>

ELX_NAMESPACE_BEGIN
class elxPerspectiveCamera : public elxCameraInterface {
    float filmToCamera;
public:
    elxPerspectiveCamera() : elxCameraInterface(), filmToCamera(1.0f) {}

    elxPerspectiveCamera(const Point3f &loc, const Point3f &lok, const Vec3f &up) : elxCameraInterface(loc, lok, up), filmToCamera(1.0f) {}

    virtual ~elxPerspectiveCamera(){
        
    }

    /*  
    pixelUV
    (0,0)__ __
        |    |
        |__ _|
             (1,1)
    */
    /// hack
    virtual float generateRay(elxRay &ray, const Point2f &pixelUV, elxSampler *sampler) const;
};
ELX_NAMESPACE_END