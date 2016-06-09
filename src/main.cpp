
#include <iostream>
#include <GLFW/glfw3.h>

#include "graphic.hpp"


// window size
static int window_w  = 640;
static int window_h = 480;

// mouse posision
static double mouse_x = 0;
static double mouse_y = 0;
void mousePosCallBack(GLFWwindow* window, double xpos, double ypos) {
  mouse_x = xpos;
  mouse_y = ypos;
}

int main() {
  if (!glfwInit()) return -1;

  auto* window = glfwCreateWindow(window_w, window_h, "2DCollisionToTexture", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetCursorPosCallback(window, mousePosCallBack);
  
  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
  
  glOrtho(0, window_w, window_h, 0, -0.0f, 1.0f);
  glViewport(0, 0, window_w, window_h);
  
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawPoint(mouse_x, mouse_y, 10);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  glfwTerminate();
  return 0;
}