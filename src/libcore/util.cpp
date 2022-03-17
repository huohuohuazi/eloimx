#include <eloimx/core/util.h>

ELX_NAMESPACE_BEGIN

ELX_NAMESPACE_END


/*
    the Fresnel reflectance is the average of the squares of the
        parallel and perpendicular polarization terms
*/
float fresnelDieletricExt(float cosThetaI_, 
    float &cosThetaT_, float eta) {
    
    if (eta == 1) {
        // no refraction
        cosThetaT_ = - cosThetaI_;
        return .0f;
    }

    /* Using Snell law */
    float scale = (cosThetaI_ > 0) ? 1/eta : eta,
          cosThetaT2 = 1 - (1 - cosThetaI_ * cosThetaI_) * (scale * scale);

    if (cosThetaT2 <= .0f) {
        // total internal reflection
        cosThetaT_ = .0f;
        return 1.f;
    }

    /* Find the absolute cosines of the incident/transmitted rays */
    float cosThetaI = std::abs(cosThetaI_);
    float cosThetaT = std::sqrt(cosThetaT2);

    float rPrl = (eta * cosThetaI - cosThetaT) / (eta * cosThetaI + cosThetaT);
    float rPpd = (cosThetaI - eta * cosThetaT) / (cosThetaI + eta * cosThetaT);
    
    cosThetaT_ = (cosThetaI_ > 0) ? -cosThetaT : cosThetaT;

    return .5f * (rPrl * rPrl + rPpd * rPpd);
}