
#pragma once

#include <iostream>
#include <cmath>

#include <GLFW/glfw3.h>

#include <fstream>
#include <vector>


bool setupTexture(const GLuint id, const std::string& path, std::vector<char>& texture_buffer) {
  std::ifstream fstr(path.c_str(), std::ios::binary);
  
  // 処理を中断
  if (!fstr) return false;
  
  // ファイルサイズを取得
  //  読み込み位置をファイル末尾へ移動
  //  ->ファイル先頭から読み込み位置までのオフセット
  //  =ファイルサイズ
  const size_t file_size = static_cast<size_t>(fstr.seekg(0, fstr.end).tellg());
  
  // 読み込み位置をファイル先頭へ戻す
  fstr.seekg(0, fstr.beg);
  
  // 動的配列を使ってファイルを読み込む場所を確保
  // charをfile_size個、メモリに確保する
  texture_buffer = std::vector<char>(file_size);
  
  // 確保した場所へファイルの内容をすべて読み込む
  fstr.read(&texture_buffer[0], file_size);
  
  
  // OpenGLに
  // 「これから、テクスチャ識別子idに対して指示を与えます」
  // と指示
  glBindTexture(GL_TEXTURE_2D, id);
  
  // 適当に画像サイズを求める
  int texture_size = std::sqrt((file_size / 4));
  
  // 1ピクセルに「赤、緑、青、α」の情報を持つ
  // 幅256ピクセル、高さ256ピクセルの画像データをOpenGLへ転送
  glTexImage2D(GL_TEXTURE_2D,
               0, GL_RGBA, texture_size, texture_size,
               0, GL_RGBA, GL_UNSIGNED_BYTE,
               &texture_buffer[0]);
  
  // 画像が拡大された場合にどう振る舞うか指定
  glTexParameteri(GL_TEXTURE_2D,
                  GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
  // 画像が縮小された場合にどう振る舞うか指定
  glTexParameteri(GL_TEXTURE_2D,
                  GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  
  std::cout << "{file path: \"" + path + "\"}" << std::endl;
  std::cout << "{buff size: " + std::to_string(file_size) + "}" << std::endl;
  std::cout << "{tex  size: " + std::to_string(texture_size) + "}" << std::endl;
  
  return true;
}


void drawTex(const Rect<float>& src) {
  // 描画する矩形の4頂点を配列で用意
  static const GLfloat vtx[] = {
    src.l, src.b,
    src.r, src.b,
    src.r, src.t,
    src.l, src.t
  };
  glVertexPointer(2, GL_FLOAT, 0, vtx);
  
  // 頂点ごとのテクスチャ座標を配列で準備
  static const GLfloat texture_uv[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f
  };
  glTexCoordPointer(2, GL_FLOAT, 0, texture_uv);
  
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  
  glEnable(GL_TEXTURE_2D);
  glEnableClientState(GL_VERTEX_ARRAY);
  
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  
  // 矩形を一つ描画
  glDrawArrays(GL_QUADS, 0, 4);
  
  // 描画が済んだら使った機能を全て無効にする
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisable(GL_TEXTURE_2D);
}