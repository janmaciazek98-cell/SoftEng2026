#pragma once
#include "IShape.h"
#include <cmath>

template <typename T> class Cone : public IShape<T> {
public:
    Cone(T radius, T height): r(radius), h(height) {}

    ShapeResult<T> compute() override
    {
        ShapeResult<T> res;
        // Objêtoœæ: V = 1/3 * PI * r^2 * h
        T volume =
            (static_cast<T>(1) / static_cast<T>(3)) * M_PI * std::pow(r, 2) * h;
        res.set_attrib(ShapeResultIndex::RESULT_VOLUME, volume);
        return res;
    }

private:
    T r, h;
};