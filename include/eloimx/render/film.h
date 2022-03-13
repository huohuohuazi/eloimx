/*
    film.h
    create: 2022.2.24
*/

#pragma once
#include <eloimx/eloimx.h>

ELX_NAMESPACE_BEGIN
class elxFilm {
public:
    Point2i resolution;

    /// default resolution 2 * 2
    elxFilm() : resolution(2, 2) {}

    elxFilm(const Point2i &resolution) : resolution(resolution) {}
};
ELX_NAMESPACE_END
