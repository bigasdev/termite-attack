#include "Termite.hpp"

#include "../core/global.hpp"
#include "../res/Res.hpp"
#include "../renderer/Renderer.hpp"
#include "../tools/Math.hpp"
#include "AffectManager.hpp"
#include "../tools/Cooldown.hpp"

#include "../renderer/Camera.hpp"

#include  "../tools/Logger.hpp"

Termite::Termite() : Entity("termite", vec2(0, 0)) {
}

Termite::Termite(std::string spr_name, vec2 _pos) : Entity(spr_name, _pos) {
}

Termite::~Termite() {
}

void Termite::update(double dt) {
  Entity::update(dt);

  if(!m_cooldown->has_state("dmg_cd")){
    can_be_damaged = true;
  }
}

void Termite::fixed_update(double tmod) {
  Entity::fixed_update(tmod);
}

void Termite::move_to(vec2 target, float speed) {
  Entity::move_to(target, speed);
}

void Termite::draw() {
  Rect collision_box = get_collision_box();
  g_renderer->draw_rect(collision_box, Col{255, 0, 0, 255}, false);
}

void Termite::damage(int damage) {
  Logger::log("Termite damaged: " + std::to_string(damage));

  if (can_be_damaged && !m_cooldown->has_state("dmg_cd")) {
    life -= damage - armor;
    can_be_damaged = false;
    m_cooldown->set_state("dmg_cd", .5f);
  }
}

bool Termite::can_collide() {
  return can_be_damaged && life > 0;
}
