
#include <iostream>
#include <vector>

#include <GLFW/glfw3.h>

#include "graphic.hpp"
#include "collision.hpp"
#include "shape.hpp"
#include "texture.hpp"


// window size
static int window_w = 640;
static int window_h = 640;

// mouse posision
static double mouse_x = 0;
static double mouse_y = 0;
void mousePosCallBack(GLFWwindow* window, double xpos, double ypos) {
  mouse_x = xpos;
  mouse_y = ypos;
}


int main() {
  //-----------------------------------------------------------
  // setup
  //-----------------------------------------------------------
  if (!glfwInit()) return -1;

  auto* window = glfwCreateWindow(window_w, window_h, "2DCollisionToTexture", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetCursorPosCallback(window, mousePosCallBack);
  
  // 60fps
  glfwSwapInterval(1);
  
  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
  
  glOrtho(0, window_w, window_h, 0, -0.0f, 1.0f);
  glViewport(0, 0, window_w, window_h);
  
  
  //-----------------------------------------------------------
  // texture
  //-----------------------------------------------------------
  
  GLuint texture_id;
  glGenTextures(1, &texture_id);
  
  std::vector<char> tex_buf;
  
  if (!setupTexture(texture_id, "../../../res/nc40027.raw", tex_buf)) {
    glDeleteTextures(1, &texture_id);
    glfwTerminate();
    return EXIT_FAILURE;
  }
  
  int tex_size = std::sqrt(tex_buf.size() / 4);
  int hasAlphaPixBySide[tex_size][tex_size];
  std::fill(hasAlphaPixBySide[0], hasAlphaPixBySide[tex_size], tex_size * tex_size);
  
  
  int index = 0;
  for (int y = 0; y < tex_size; y++) {
    for (int x = 0; x < tex_size; x++) {
      // Alpha値の有るPixか調べる
      // Alpha値があれば通過
      if (!(int)(unsigned char)tex_buf[index + 3]) {
        index += 4;
        continue;
      }
      
      // 画面はじか調べる
      if ((!y || (y == tex_size - 1)) ||
          (!x || (x == tex_size - 1))) {
        
        hasAlphaPixBySide[y][x] = 1;
        index += 4;
        continue;
      }
      
      // 左右
      if ((int)(unsigned char)tex_buf[index - 1] <= 5) {
        hasAlphaPixBySide[y][x] = 1;
      }
      if ((int)(unsigned char)tex_buf[index + 7] <= 5) {
        hasAlphaPixBySide[y][x] = 1;
      }
      
      // 上下
      if ((int)(unsigned char)tex_buf[index + 3 - (512 * 4)] <= 5) {
        hasAlphaPixBySide[y][x] = 1;
      }
      if ((int)(unsigned char)tex_buf[index + 3 + (512 * 4)] <= 5) {
        hasAlphaPixBySide[y][x] = 1;
      }
      
      index += 4;
    }
  }
  
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor4f(1, 1, 1, 1);
    
    Rect<float> rect(0, 512, 512, 0);
    drawTex(rect);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  glfwTerminate();
  return 0;
}