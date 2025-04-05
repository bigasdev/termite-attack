#include "Rect_Object.hpp"
#include "../../core/global.hpp"
#include "../../renderer/Renderer.hpp"

Rect_Object::Rect_Object(Rect rect, Col color, bool fill, bool border, int border_width, Col border_color)
{
  this->rect = rect;
  this->color = color;
  this->fill = fill;
  this->border = border;
  this->border_width = border_width;
  this->border_color = border_color;
}

Rect_Object::~Rect_Object()
{
  dispose();
}

void Rect_Object::awake()
{
}

void Rect_Object::start()
{
}

void Rect_Object::show()
{
  is_visible = true;
}

void Rect_Object::hide()
{
  is_visible = false;
}

void Rect_Object::update(double dt)
{
}

void Rect_Object::draw()
{
  if (fill)
  {
    g_renderer->draw_rect({get_pos().x, get_pos().y, rect.w, rect.h}, color,true);
  }

  if (border)
  {
    for (int i = 0; i < border_width; i++)
    {
      g_renderer->draw_rect(Rect{get_pos().x + i, get_pos().y + i, rect.w - i * 2, rect.h - i * 2}, border_color,false);
    }
  }
}

void Rect_Object::dispose()
{
}
