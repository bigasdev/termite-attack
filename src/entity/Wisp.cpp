#include "Wisp.hpp"
#include "../core/global.hpp"
#include "../res/Res.hpp"
#include "../tools/Math.hpp"
#include "AffectManager.hpp"
#include "../tools/Cooldown.hpp"
#include "../renderer/Camera.hpp"
#include  "../tools/Logger.hpp"

Wisp::Wisp() : Entity("wisp", vec2(0, 0)) {
}

Wisp::Wisp(std::string spr_name, vec2 _pos) : Entity(spr_name, _pos) {
  SpriteFrame idle = g_res->get_animation("idle");
  idle.frame_timer = .24f;
  idle.orig_x = spr.dst_x;
  idle.orig_y = spr.dst_y;
  idle.state = &is_idle;
  
  frict_x = 1;
  frict_y = 1;
  z_gravity = 0;

  animator->register_anim(idle);
}

Wisp::~Wisp() {
}

void Wisp::update(double dt) {
  Entity::update(dt);

  if(!is_attached){
    dy += z_gravity * dt;
  }
}

void Wisp::fixed_update(double tmod) {
  Entity::fixed_update(tmod);
}

void Wisp::move_to(vec2 target, float speed) {
  Entity::move_to(target, speed);
}

void Wisp::dettach() {
  is_attached = false;
  dy = -speed + speed_add;
  m_cooldown->set_state("dettach", 0.15f);
}

void Wisp::bump(vec2 from) {
  if(m_cooldown->has_state("dettach") || m_cooldown->has_state("attacked"))return;
  
  if(pos.x < from.x){
    dx = speed + speed_add;
    dy = speed + speed_add;
  }

  if(pos.x > from.x){
    dx = -speed - speed_add;
    dy = speed + speed_add;
  }

  m_cooldown->set_state("attacked", 0.05f);
}

void Wisp::wall_bump(int multiplier) {
  if(m_cooldown->has_state("dettach"))return;
  dx = speed * multiplier;
}

void Wisp::launch(vec2 from) {
  if(m_cooldown->has_state("dettach") || is_attached)return;

  if(pos.x < from.x){
    dx = -speed - speed_add;
    dy = -speed - speed_add;
  }

  if(pos.x > from.x){
    dx = speed + speed_add;
    dy = -speed - speed_add;
  }
  if(Math::approx(pos.x, from.x, 20)){
    dx = 0;
    dy = -speed - speed_add;
  }
}

