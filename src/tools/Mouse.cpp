#include "Mouse.hpp"
#include "SDL.h"
#include <cmath>
#include <cstdlib>

#include "../core/global.hpp"
#include "../renderer/Camera.hpp"

namespace Mouse{
  bool is_clicked;
}

bool Mouse::is_at_area(Rect pArea) {
  int x = 0, y = 0;
  SDL_GetMouseState(&x, &y);

  // explanation of the magic numbers:
  // 4 are used to smoothen the edge-case detection
  // 8x8 is the width of the default cursor
  Rect mouseArea = Rect(x - 4, y - 4, 8, 8);
  return mouseArea.intersects(pArea);
}

Rect Mouse::get_mouse_area(int width, int height) {
  int x = 0, y = 0;
  SDL_GetMouseState(&x, &y);

  int scaled_x = x * 64/width;
  int scaled_y = y * 64/height;

  return Rect(scaled_x - 4, scaled_y - 4, 8, 8);
}

vec2 Mouse::get_mouse_pos() {
  int x = 0, y = 0;
  SDL_GetMouseState(&x, &y);
  return vec2(x, y);
}

//TECH DEBT 1601
vec2 Mouse::get_mouse_coordinates(float min, float max) {
  int x = 0, y = 0;
  SDL_GetMouseState(&x, &y);
  x -= 8 * g_camera->get_game_scale();
  y -= 8 * g_camera->get_game_scale();

  float game_x = min + (static_cast<float>(x)/360) * (max - min);
  float game_y = -320 + (static_cast<float>(y)/640) * (320 - -320);
  return vec2(game_x, game_y);
}

bool Mouse::is_at_game_area(Rect pArea) {
  vec2 coordinates = get_mouse_pos();

  Rect mouseArea = Rect(coordinates.x, coordinates.y, 8*g_camera->get_game_scale(), 8*g_camera->get_game_scale());
  return mouseArea.intersects(pArea);
}


float Mouse::get_mouse_angle(vec2 pos) {
  vec2 mousePos = get_mouse_pos();
  return std::atan2(mousePos.y - pos.y, mousePos.x - pos.x);
}
