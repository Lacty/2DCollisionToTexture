
#pragma once
#include "shape.hpp"


template<typename T>
bool isCollision(T x, T y, Rect<T> src) {
  if (x <= src.r && x >= src.l) {
    if (y <= src.t && y >= src.b) {
      return true;
    }
  }
  return false;
}

template<typename T>
bool isCollision(const Rect<T>& src1, const Rect<T>& src2) {
  if (src1.r >= src2.l) {
    if (src1.l <= src2.r) {
      if (src1.t >= src2.b) {
        if (src1.b <= src2.t) {
          return true;
        }
      }
    }
  }
  return false;
}