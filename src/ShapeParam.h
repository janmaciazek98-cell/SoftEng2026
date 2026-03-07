#ifndef _SHAPEPARAM_H
#define _SHAPEPARAM_H


#include <vector>
using namespace std;
#include "ShapeType.h"
#include "ShapeParamIndex.h"

template<class T>
class ShapeParam {
  private:
    vector<T> attribs;


  public:
    ShapeType type;

    inline T get(ShapeParamIndex ind) const;

    inline bool set(ShapeParamIndex ind, const T & val);

    inline bool validate() const;

};
template<class T>
inline T ShapeParam<T>::get(ShapeParamIndex ind) const {
    return attribs[ind];
}

template<class T>
inline bool ShapeParam<T>::set(ShapeParamIndex ind, const T & val) {
  return true;
}

template<class T>
inline bool ShapeParam<T>::validate() const {
  return true;
}

#endif
