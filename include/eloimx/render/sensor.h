/*
    sensor.h
    create: 2022.2.24
*/

#pragma once

#include <eloimx/eloimx.h>
#include <eloimx/render/film.h>

ELX_NAMESPACE_BEGIN
class elxSampler;
class elxCameraInterface {
protected:
    Point3f location, lookAt;
    Vec3f up;
    elxFilm *film;
    //const Medium *medium; 
public:
    /// default, the camera locates at 0,0,-1, look at 0,0,0, up is 0,1,0
    elxCameraInterface() :location(0,0,-1), lookAt(0,0,0), up(0,1,0), film(new elxFilm()) {}

    elxCameraInterface(const Point3f &loc, const Point3f &lok, const Vec3f &up) : location(loc), lookAt(lok), up(up), film(new elxFilm()) {}

    virtual ~elxCameraInterface() {
        delete film;
    }

    /// return the weight of the ray
    virtual float generateRay(elxRay &ray, const Point2f &pixelUV, elxSampler *sampler) const = 0;
};


ELX_NAMESPACE_END
