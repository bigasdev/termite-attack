#pragma once
#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "Common.hpp"
namespace Mouse
{

  bool is_at_area(Rect pArea);
  Rect get_mouse_area(int width, int height);
  vec2 get_mouse_pos();
  vec2 get_mouse_coordinates(float min = -180, float max = 180);
  bool is_at_game_area(Rect pArea);
  float get_mouse_angle(vec2 pos);

  extern bool is_clicked;
}; // namespace Mouse

#endif
