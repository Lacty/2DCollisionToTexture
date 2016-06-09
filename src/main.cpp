//
// 配列データをまとめて指定
//   WindowsでOpenGL1.1以降の機能を使うには
//   GLEWが必要
//

#include <GLFW/glfw3.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <iostream>

//#include "cube.h"         // 立方体のデータ
#include "torus.h"        // トーラスのデータ
//#include "monkey.h"
#include "hourglass.h"


// degrees -> radians
float toRadians(float degrees) {
  return degrees * M_PI / 180.0f;
}

// radians -> degrees
float toDegrees(float radians) {
  return radians * 180.0f / M_PI;
}


// 縦横比に応じてfovyを計算
// fov   横長画面の時のfov
// aspect 縦横比(w/h)
// near_z
float calcFovy(const float fov, const float aspect, const float near_z) {
  if (aspect >= 1.0f) return fov;
  
  // 画面が縦長になったら、幅基準でfovを求める
  // fovとnear_zから投影面の幅の半分を求める
  float half_w = std::tan(toRadians(fov / 2)) * near_z;
  
  // 表示画面の縦横比から、投影面の高さの半分を求める
  float half_h = half_w / aspect;
  
  // 投影面の高さの半分とnear_zから、fovが求まる
  return toDegrees(std::atan(half_h / near_z) * 2);
}


// 透視変換行列を作成
//
// fovy 視野角(縦) degree
// aspect 縦横比(w/h)
// near_z, far_z
Eigen::Matrix4f perspectiveView(float fovy,
                                float aspect,
                                float near_z,
                                float far_z) {
  Eigen::Matrix4f m;  // 4x4の行列を作成
  
  float fovy_rad = toRadians(fovy);
  float f        = 1.0f / (tan(fovy_rad / 2.0f));
  float d        = (far_z - near_z);
  
  m << f / aspect, 0.0f,                  0.0f,                         0.0f,
  0.0f,    f,                  0.0f,                         0.0f,
  0.0f, 0.0f, -(far_z + near_z) / d, -(2.0f * far_z * near_z) / d,
  0.0f, 0.0f,                 -1.0f,                         0.0f;
  
  return m;
}


// Windowのサイズ
int window_width  = 800;
int window_height = 600;


// Windowがリサイズされた時に呼び出される
void resize(GLFWwindow *, int width, int height) {
  window_width  = width;
  window_height = height;
}

// 立方体の描画
void drawCube() {
  for (int i = 0; i < OBJECTS_COUNT; i++) {
    // 描画に使う配列を有効にする
    glEnableClientState(GL_INDEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    // 頂点配列のストライド指定を使う
    //   ストライドは、配列データの隙間のデータサイズを指定する
    glVertexPointer(3, GL_FLOAT, sizeof(vertex_struct), &vertices[vertex_offset_table[i]].x);
    glNormalPointer(GL_FLOAT, sizeof(vertex_struct), &vertices[vertex_offset_table[i]].nx);
    glTexCoordPointer(2, GL_FLOAT, sizeof(vertex_struct), &vertices[vertex_offset_table[i]].u);
    
    glPushMatrix();
    glMultMatrixf(&transformations[i][0]);
    
    // 配列のインデックス情報をもとに三角形を描
    glDrawElements(GL_TRIANGLES, faces_count[i] * 3, GL_UNSIGNED_SHORT, &indexes[indices_offset_table[i]]);
    glPopMatrix();
    
    // 使い終わったら後始末
    glDisableClientState(GL_INDEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}


int main() {
  if (!glfwInit()) return -1;
  
  GLFWwindow* window = glfwCreateWindow(window_width, window_height,
                                        "glInterleavedArrays sample",
                                        nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }
  
  glfwSetWindowSizeCallback(window, resize);
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);
  
  // ライティングを有効にする
  glEnable(GL_LIGHTING);
  // 0番のライトを有効にする
  glEnable(GL_LIGHT0);
  // 法線を正規化する
  glEnable(GL_NORMALIZE);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  
  
  float angle = 0.0f;
  
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glViewport(0, 0, window_width, window_height);
    
    float aspect = window_width / float(window_height);
    float fov    = 35.0f;
    float near_z = 0.5f;
    
    float fovy = calcFovy(fov, aspect, near_z);
    Eigen::Matrix4f m = perspectiveView(fovy, aspect, near_z, 100.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(m.data());
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glTranslatef(0.0f, 0.0f, -20.0f);
    //glRotatef(-90, 1, 0, 0);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    //glRotatef(angle, 1.0f, 0.0f, 0.0f);
    angle += 0.5f;
    
    
    
    // 光源の位置
    //  カレント行列により結果が決まる
    //  wの値が1.0だとポイントライトになる
    GLfloat position[] = { 0.0f, 0.0f, -10.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    // 拡散光
    GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    
    // 環境光
    GLfloat ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    
    // スペキュラ
    GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    
    
    // マテリアル(材質)の設定
    //  環境光が当たった時の色味
    GLfloat mat_amb[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
    
    // 拡散光が当たった時の色味
    GLfloat mat_diff[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diff);
    
    // 自己発光
    GLfloat mat_emi[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emi);
    
    // 光沢の色味
    GLfloat mat_spe[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spe);
    
    // 光沢の加減
    //  値が小さいほど鋭い光沢になる
    GLfloat mat_shin = 80.0f;
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shin);
    
    
    drawCube();
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  glfwTerminate();
}
