
#include <iostream>
#include <GLFW/glfw3.h>

#include "graphic.hpp"


// window size
static int w_width  = 640;
static int w_height = 480;

int main() {
  if (!glfwInit()) return -1;

  auto* window = glfwCreateWindow(w_width, w_height, "2DCollisionToTexture", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
  
  glOrtho(0, w_width, w_height, 0, -0.0f, 1.0f);
  glViewport(0, 0, w_width, w_height);
  
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawPoint(0, 0, 10);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  glfwTerminate();
  return 0;
}