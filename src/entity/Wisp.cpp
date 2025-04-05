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
  dy = -35;
}
