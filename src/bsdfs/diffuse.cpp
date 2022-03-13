#include <eloimx/bsdfs/diffuse.h>

ELX_NAMESPACE_BEGIN
// todo
elxSpectrum elxDiffuse::sample(elxBSDFSamplingRecord &bRec, const Point2f &sample) const {
    std::cout<<"This should not be executed, sample function\n";
    if (elxFrame::cosTheta(bRec.wi) <= 0){
        return elxSpectrum(.0f);
    }
    //bRec.wo
    return color;
}
// todo
elxSpectrum elxDiffuse::sample(elxBSDFSamplingRecord &bRec, const Point2f &sample, float &pdf) const {
    if (elxFrame::cosTheta(bRec.wi) <= 0)
        return elxSpectrum(.0f);
    
    bRec.wo = warp::squareToCosHemisphere(sample);
    bRec.eta = 1.0f;
    pdf = warp::squareToCosHemispherePdf(bRec.wo);
    return color;
}
// todo
elxSpectrum elxDiffuse::eval(const elxBSDFSamplingRecord &bRec) const {
    if (elxFrame::cosTheta(bRec.wi) <= 0 ||
        elxFrame::cosTheta(bRec.wo) <= 0) {
        return elxSpectrum(.0f);
    }

    return color * (INV_PI * elxFrame::cosTheta(bRec.wo));
}
// todo
float elxDiffuse::pdf(const elxBSDFSamplingRecord &bRec) const {
    if (elxFrame::cosTheta(bRec.wi) <= 0 ||
        elxFrame::cosTheta(bRec.wo) <= 0) {
        return .0f;
    }
    return warp::squareToCosHemispherePdf(bRec.wo);
}

std::string elxDiffuse::toString() const {
    return fmt::format("Here is a constant diffuse, which color is [{}, {}, {}]",
        color.r, color.g, color.b);
}

ELX_NAMESPACE_END