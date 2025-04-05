#include "Button.hpp"
#include "../../core/global.hpp"
#include "../../renderer/Renderer.hpp"
#include "../../res/Res.hpp"
#include <iterator>

Button::Button(Rect rect, std::string name, std::string text, Col col) {
  this->pos = vec2{pos.x + rect.x, pos.y + rect.y};
  this->rect = rect;
  this->name = name;
  this->text = text;
  this->col = col;

  awake();
}

Button::Button(std::string name, std::string spr_name, vec2 pos,
               Rect coll_rect) {
  this->name = name;
  this->coll_rect = coll_rect;
  this->pos = pos;
  this->spr = g_res->get_sprite(spr_name);
}

void Button::start(){

}

void Button::awake() {
}

Button::~Button() { this->dispose(); }

Rect Button::get_click_area() {
  if (this->text == "") {
    return Rect{pos.x - this->coll_rect.x, pos.y - this->coll_rect.y,
                coll_rect.w, coll_rect.h};
  } else {
    return this->rect;
  }
}

void Button::show() {
  is_visible = true;
}

void Button::hide() {
  is_visible = false;
}

void Button::update(double dt) {
  this->rect.x = get_pos().x;
  this->rect.y = get_pos().y;
}

void Button::draw() {
  if (!is_visible)
    return;
  if (this->text == "") {
    g_renderer->draw(*g_res->get_texture(spr.sheet), spr, pos);
#if _DEBUG
    g_renderer->draw_rect(Rect{get_pos().x - this->coll_rect.x,
                               get_pos().y - this->coll_rect.y, coll_rect.w,
                               coll_rect.h},
                          {0, 255, 0, 150}, false);
#endif
  } else {
    // we should add support for outline only buttons later
    g_renderer->draw_rect(this->rect, this->col, true);
    // support for differnet fonts and size, maybe create a struct just for the
    // text
    g_renderer->draw_text(
        vec2(this->rect.x + this->rect.w / 2, this->rect.y + this->rect.h / 2),
        this->text.c_str(), g_res->get_font("arial"), {255, 255, 255, 255});
#if _DEBUG
    g_renderer->draw_rect(this->rect, {0, 255, 0, 150}, false);
#endif
  }
}

void Button::dispose() {}

void Button::on_click() {
  if (this->is_enabled) {
    this->is_clicked = true;
    if (this->on_click_callback != nullptr)
      this->on_click_callback();
    this->is_clicked = false;
  }
}

void Button::on_enable() {
  if (!this->is_enabled) {
    this->is_enabled = true;
    if (this->on_enable_callback != nullptr)
      this->on_enable_callback();
  }
}

void Button::on_disable() {
  if (this->is_enabled) {
    this->is_enabled = false;
    if (this->on_disable_callback != nullptr)
      this->on_disable_callback();
  }
}

void Button::on_hover() {
  if (!this->is_hovered) {
    this->is_hovered = true;
    if (this->on_hover_callback != nullptr)
      this->on_hover_callback();
  }
}

void Button::on_leave() {
  if (this->is_hovered) {
    this->is_hovered = false;
    if (this->on_leave_callback != nullptr)
      this->on_leave_callback();
  }
}

void Button::set_on_click(std::function<void()> on_click) {
  this->on_click_callback = on_click;
}

void Button::set_on_enable(std::function<void()> on_enable) {
  this->on_enable_callback = on_enable;
}

void Button::set_on_disable(std::function<void()> on_disable) {
  this->on_disable_callback = on_disable;
}

void Button::set_on_hover(std::function<void()> on_hover) {
  this->on_hover_callback = on_hover;
}

void Button::set_on_leave(std::function<void()> on_leave) {
  this->on_leave_callback = on_leave;
}
