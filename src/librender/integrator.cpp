#include <eloimx/render/integrator.h>
ELX_NAMESPACE_BEGIN

bool elxRadianceQueryRecord::rayIntersect(const elxRay &ray) {
    // ignore the medium situation first
    scene->rayIntersect(ray, its);
    return its.isValid();
}

void elxSamplingIntegrator::render(
    elxScene *scene, 
    elxRenderJob *job,
    elxCameraInterface *sensor) const {
    // do the render job
    float invU = 1.0f / job->width, invV = 1.0f / job->height;
    elxSampler sampler;
    for (int u = 0; u < job->width; ++u){
        for (int v = 0; v < job->height; ++v) {
            elxRay ray;
            Point2f uv = Point2f(u, v);
            uv *= Point2f(invU, invV);

            elxSpectrum spectrum(.0f);
            for (int i = 0; i < job->spp; ++i){
                sensor->generateRay(ray, uv, &sampler);
                elxRadianceQueryRecord bRec(scene, &sampler);
                spectrum += Li(ray, bRec);
            }
            spectrum /= (float)job->spp;
            
            job->setPixel(u, v, spectrum);
        }
    }
    job->writeTga();
}

ELX_NAMESPACE_END