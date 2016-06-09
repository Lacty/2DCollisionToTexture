
#pragma once


template<typename T>
class Rect {
public:
  T l, r, t, b;
  
  Rect(T l, T r, T t, T b) : l(l), r(r), t(t), b(b) {}
  Rect(const Rect& src) : l(src.l), r(src.r), t(src.t), b(src.b) {}
};