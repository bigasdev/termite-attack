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

  bool is_attached = true;
private:
  bool is_idle = true;
};
