/*
    integrator.h
    create: 2022.2.25
*/

#pragma once

#include <eloimx/eloimx.h>
#include <eloimx/render/scene.h>
#include <eloimx/render/sampler.h>
#include <eloimx/render/intersection.h>
#include <eloimx/render/sensor.h>
#include <eloimx/render/renderjob.h>
ELX_NAMESPACE_BEGIN

class elxIntegratorInterface {

public:

    // for possible preProcess
    virtual void preProcess(elxScene *scene) {
        return; 
    }

    // must be implement in subclass
    virtual void render(elxScene *scene, 
                        elxRenderJob *job,
                        elxCameraInterface *sensor) const = 0;

protected:
    elxIntegratorInterface(){ }
};

struct elxRadianceQueryRecord {

    // pointer to the scene to be rendered
    const elxScene *scene;

    // sample generator
    elxSampler *sampler;

    // pointer to the current medium
    // const Medium *medium;

    // current depth value
    int depth;

    // information of the hitted point and its surface
    elxIntersection its;

    elxRadianceQueryRecord(const elxScene *scene, elxSampler *sampler)
        :scene(scene), sampler(sampler), depth(0) {}

    bool rayIntersect(const elxRay &ray);


};

class elxSamplingIntegrator : public elxIntegratorInterface {
public:


    // estimate the incident radiance along a ray
    virtual elxSpectrum Li(const elxRay &ray, 
        elxRadianceQueryRecord &bRec) const = 0;

    // estimate the irrdiance at a given surface point
    // the default implementation simply samples the hemisphere using
    // cosine-weighted sampling and a configurable number of rays 
    //virtual elxSpectrum E(const elxScene *scene, 
    //  const elxIntersection &its, const Medium *medium,
    //  elxSampler *sampler, 
    //  int nSamples, bool includeIndirect) const;


    //  perform the main rendering task
    virtual void render(elxScene *scene, 
                        elxRenderJob *job,
                        elxCameraInterface *sensor) const;

protected:
    elxSamplingIntegrator() { }
};

class elxMCIntegrator : public elxSamplingIntegrator {
public:

protected:
    elxMCIntegrator() {}
    elxMCIntegrator(int maxDepth, int rrDepth, bool strictNormals, bool hideEmitters )
    :m_maxDepth(maxDepth), m_rrDepth(rrDepth),
     m_strictNormals(strictNormals), m_hideEmitters(hideEmitters) { }

    int m_maxDepth;
    int m_rrDepth;
    bool m_strictNormals;
    bool m_hideEmitters;
};

/*
    implement class
*/

ELX_NAMESPACE_END