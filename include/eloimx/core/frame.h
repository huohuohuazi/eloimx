#pragma once
#include<eloimx/eloimx.h>

ELX_NAMESPACE_BEGIN

struct elxFrame {
    Vec3f Xprime, Zprime;
    Vec3f Yprime;       // the normal

    elxFrame() { }

    elxFrame(const Vec3f &normal);

    elxFrame(const Vec3f &X, 
        const Vec3f &Y, const Vec3f &Z):Xprime(X), Yprime(Y), Zprime(Z) {}

    Vec3f toLocal(const Vec3f &v) const;

    Vec3f toWorld(const Vec3f &v) const;

    // assume that the vector is in the local coordinate
    static float cosTheta2(const Vec3f &v);

    static float cosTheta(const Vec3f &v);

    static float sinTheta(const Vec3f &v);

    std::string toString() const;



};

ELX_NAMESPACE_END