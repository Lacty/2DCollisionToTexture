
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