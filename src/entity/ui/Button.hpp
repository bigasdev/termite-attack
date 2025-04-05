#pragma once 

#include <string>
#include <functional>
#include "../../tools/Common.hpp"
#include "../../renderer/Sprite.hpp"
#include "Object.hpp"


class Button : public Object
{
public:

  Button(Rect rect, std::string name, std::string text, Col col);
  Button(std::string name, std::string spr_name, vec2 pos, Rect coll_rect);
  ~Button();

  void awake() override;
  void start() override;
  void show() override;
  void hide() override;
  void update(double dt) override;
  void draw() override;
  void dispose() override;

  void on_click();
  void on_enable();
  void on_disable();
  void on_hover();
  void on_leave();

  Rect get_click_area();

  void set_on_click(std::function<void()> on_click);
  void set_on_enable(std::function<void()> on_enable);
  void set_on_disable(std::function<void()> on_disable);
  void set_on_hover(std::function<void()> on_hover);
  void set_on_leave(std::function<void()> on_leave);

  bool is_clicked = false;
  bool is_enabled = true;
  bool is_hovered = false;
  std::string name;

private:
  Rect coll_rect;
  Sprite spr;
  std::string text = "";
  Col col;

  std::function<void()> on_click_callback;
  std::function<void()> on_enable_callback;
  std::function<void()> on_disable_callback;
  std::function<void()> on_hover_callback;
  std::function<void()> on_leave_callback;
};
