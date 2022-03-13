/*
    path.h
    create: 2022.3.4
*/
#pragma once
#include<eloimx/eloimx.h>
#include<eloimx/render/integrator.h>
ELX_NAMESPACE_BEGIN

class elxPathTracer : public elxMCIntegrator {
    elxPathTracer() {}
protected:
    float miWeight(float pdfA, float pdfB) const;
public:    
    elxPathTracer(int maxDepth, int rrDepth, bool strictNormals, bool hideEmitters)
    : elxMCIntegrator(maxDepth, rrDepth, strictNormals, hideEmitters) { }

    virtual elxSpectrum Li(const elxRay &ray, 
        elxRadianceQueryRecord &bRec) const;

};

ELX_NAMESPACE_END