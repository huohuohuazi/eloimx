#pragma once
#include <eloimx/eloimx.h>

/*
    cosThetaI : Cosine of the angle between the normal and the incident ray
        (may be negative)
    cosThetaT : Argument used to return the cosine of the angle between the normal
        and the transmitted ray, will have the opposite sign of cosThetaI
    float eta : relative refractive index
*/
float fresnelDieletricExt(float cosThetaI, 
    float &cosThetaT, float eta);