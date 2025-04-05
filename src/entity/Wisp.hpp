#pragma once

#include "Entity.hpp"

class Wisp : public Entity {
public:
  Wisp();
  Wisp(std::string spr_name, vec2 _pos);
  ~Wisp();

  void update(double dt) override;
  void fixed_update(double tmod) override;
  void move_to(vec2 target, float speed = 0) override;

  void dettach();
  void bump(vec2 from);
  void wall_bump(int multiplier);
  void launch(vec2 from);

  bool is_attached = true;

  //stats 
  int attack = 10;
  int speed_add = 0;
  int endurance = 5;
  int luck = 0;
private:
  bool is_idle = true;
  int speed = 4;
};
