#pragma once

#include "Entity.hpp"
class Termite : public Entity {
public:
  Termite();
  Termite(std::string spr_name, vec2 _pos);
  ~Termite();

  void update(double dt) override;
  void fixed_update(double tmod) override;
  void move_to(vec2 target, float speed = 0) override;

  void draw();
  void damage(int damage);
  bool can_collide();

private:
  bool can_be_damaged = true;
};
