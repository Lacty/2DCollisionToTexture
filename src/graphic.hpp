
#pragma once

#include <GLFW/glfw3.h>
#include "shape.hpp"


void drawPoint(float x, float y, float size) {
  // 点を描画する位置を指定
  GLfloat vtx[] = { x, y };
  
  // 描画に使う頂点の配列をOpenGLに指定
  glVertexPointer(2, GL_FLOAT, 0, vtx);
  
  // 描画する点のサイズ指定
  glPointSize(size);
  
  // 点を描画
  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawArrays(GL_POINTS, 0, 1);
  
  glDisableClientState(GL_VERTEX_ARRAY);
}

void drawLine(float start_x, float start_y,
              float end_x, float end_y,
              float width) {
  // 描画する線分の始点と終点の座標(X, Y)を指定
  GLfloat vtx[] = {
    start_x, start_y,
    end_x, end_y
  };
  
  glVertexPointer(2, GL_FLOAT, 0, vtx);
  
  // 線分の太さを指定
  glLineWidth(width);
  
  // 描画
  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawArrays(GL_LINES, 0, 2);
  
  glDisableClientState(GL_VERTEX_ARRAY);
}

template<typename T>
void drawRect(const Rect<T>& src) {
  drawLine(src.l, src.t, src.r, src.t, 1); // top
  drawLine(src.l, src.t, src.l, src.b, 1); // left
  drawLine(src.r, src.t, src.r, src.b, 1); // right
  drawLine(src.l, src.b, src.r, src.b, 1); // bottom
}