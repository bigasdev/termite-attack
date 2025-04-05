#pragma once 
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../tools/Common.hpp"
#include "../renderer/Sprite.hpp"
#include "random.hpp"

class Cooldown;
class AffectManager;

using Random = effolkronium::random_static;

class Entity{
public:
  Entity();
  Entity(std::string spr_name, vec2 _pos);
  ~Entity();

  virtual void update(double dt);
  virtual void fixed_update(double tmod);
  virtual void move_to(vec2 target, float speed = 0);

  Rect get_collision_box();

   
  Sprite spr;
  //
  vec2 pos;
  //
  int life = 100;
  int max_life = 100;
  int armor = 0;
  //velocity
  float dx = 0.0, dy = 0.0;
  //
  Cooldown* m_cooldown;
  //used to add debuffs or buffs to the entity, it has a strength priority system too
  AffectManager* m_affect_manager;
  //used to animate the Entity
  SpriteAnimator *animator;
private:

  
  float frict_x = 0.98f , frict_y = 0.98f;
  //gravity stuff 
  float dz = 0.0, zr = 0.0;
  float z_gravity = 0.027;

  //bump velocity, used to bumpers or speeders 
  float bd_x = 0.0, bd_y = 0.0;
  float bd_frict = 0.93f;

  //dodge velocity, for rolls and dashes
  float dd_x = 0.0, dd_y = 0.0;
  float dd_frict = 0.96f;

  Entity *last_dmg_source = nullptr;
  Entity *last_heal_source = nullptr;
  Entity *target = nullptr;
};

#endif
