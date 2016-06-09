
#pragma once

#include <GLFW/glfw3.h>


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