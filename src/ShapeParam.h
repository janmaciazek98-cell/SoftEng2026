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

    inline T get_attrib(ShapeParamIndex ind) const;

    inline bool set_attrib(ShapeParamIndex ind, const T & val);

    inline bool validate() const;

};
template<class T>
inline T ShapeParam<T>::get_attrib(ShapeParamIndex ind) const {
    if(ind<attribs.size()) return attribs[ind];
    return 0;
}

template<class T>
inline bool ShapeParam<T>::set_attrib(ShapeParamIndex ind, const T & val) {
  if(ind>=attribs.size())attribs.resize(ind+1);
  attribs[ind]=val;
  return true;
}

template<class T>
inline bool ShapeParam<T>::validate() const {
  switch (type) {
    case PT_CYLINDER:
    {
      T r = get_attrib(ShapeParamIndex::PARAM_RADIUS);
      T h = get_attrib(ShapeParamIndex::PARAM_HEIGHT);

      if (r < static_cast<T>(0) || h < static_cast<T>(0))
      {
        throw std::invalid_argument("Promien i wysokosc nie moga byc ujemne");
      }
      break;
    }

    default:
      break;
  }

  return true;
}

#endif
