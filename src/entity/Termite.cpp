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
