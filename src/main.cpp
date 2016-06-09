
#include <iostream>
#include <GLFW/glfw3.h>


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
  
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  glfwTerminate();
  return 0;
}