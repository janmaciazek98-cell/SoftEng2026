#ifndef _ELLIPSOID_H
#define _ELLIPSOID_H

#include "Shape3D.h"
#include "ShapeResult.h"
#include <string>
#include <cmath>
#include <iostream>
#include "ShapeParam.h"

using namespace std;

template<class T>
class Ellipsoid : public Shape3D<T> {
public:
    inline virtual ShapeResult<T> compute();

    inline string print();
    inline Ellipsoid(const ShapeParam<T>& param);
};

template<class T>
inline ShapeResult<T> Ellipsoid<T>::compute() {
    ShapeResult<T> results;
    const T PI = static_cast<T>(3.141592653589793);

    T a = this->param.values[0];
    T b = this->param.values[1];
    T c = this->param.values[2];

    results.volume = (static_cast<T>(4) / 3) * PI * a * b * c;

    T p = static_cast<T>(1.6075);
    T term1 = pow(a * b, p);
    T term2 = pow(a * c, p);
    T term3 = pow(b * c, p);

    results.surfaceArea = 4 * PI * pow((term1 + term2 + term3) / 3, 1.0 / p);

    return results;
}

template<class T>
inline string Ellipsoid<T>::print() {
    return "Bryla: Elipsoida. Obliczono objetosc i pole powierzchni calkowitej.";
}

template<class T>
inline Ellipsoid<T>::Ellipsoid(const ShapeParam<T>& param) : Shape3D<T>(param) {
}

#endif