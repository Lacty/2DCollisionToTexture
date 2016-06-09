
#include <iostream>
#include <vector>

#include <GLFW/glfw3.h>

#include "graphic.hpp"
#include "collision.hpp"
#include "shape.hpp"
#include "texture.hpp"


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
  
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    Rect<float> rect(0, 256, 256, 0);
    drawTex(rect);
    drawRect(rect);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  glfwTerminate();
  return 0;
}