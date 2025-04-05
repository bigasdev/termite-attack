#include "Canvas.hpp"
#include "../../tools/Logger.hpp"

Canvas::Canvas(vec2 size, vec2 padding_vert, vec2 padding_hor, Col background_color)
{
  this->size = size;
  this->padding_vert = padding_vert;
  this->padding_hor = padding_hor;
  this->background_color = background_color;
}

Canvas::~Canvas()
{
  dispose();
}

void Canvas::awake()
{
}

void Canvas::start()
{
  for (Object *child : children)
  {
    child->start();


    if (alignment == TOP_LEFT)
    {
      child->pos += vec2{pos.x + (child->rect.x) + padding_hor.x, pos.y + (child->rect.y) + padding_vert.y};
    }
    else if (alignment == TOP_CENTER)
    {
      child->pos += vec2{pos.x + (child->rect.x) + size.x / 2 - child->rect.w / 2, pos.y + (child->rect.y) + padding_vert.y};
    }
    else if (alignment == TOP_RIGHT)
    {
      child->pos += vec2{pos.x + (child->rect.x) + size.x - child->rect.w - padding_hor.x, pos.y + (child->rect.y) + padding_vert.y};
    }
    else if (alignment == CENTER_LEFT)
    {
      child->pos += vec2{pos.x + (child->rect.x) + padding_hor.x, pos.y + (child->rect.y) + size.y / 2 - child->rect.h / 2};
    }
    else if (alignment == CENTER)
    {
      child->pos += vec2{pos.x + (child->rect.x) + size.x / 2 - child->rect.w / 2, pos.y + (child->rect.y) + size.y / 2 - child->rect.h / 2};
    }
    else if (alignment == CENTER_RIGHT)
    {
      child->pos += vec2{pos.x + (child->rect.x) + size.x - child->rect.w - padding_hor.x, pos.y + (child->rect.y) + size.y / 2 - child->rect.h / 2};
    }
    else if (alignment == BOTTOM_LEFT)
    {
      child->pos += vec2{pos.x + (child->rect.x) +padding_hor.x, size.y - (child->rect.y) - (child->rect.h) - padding_vert.y};
    }
    else if (alignment == BOTTOM_CENTER)
    {
      child->pos += vec2{pos.x + (child->rect.x) + size.x / 2 - child->rect.w / 2, pos.y + size.y - (child->rect.y) - child->rect.h - padding_vert.y};
    }
    else if (alignment == BOTTOM_RIGHT)
    {
      child->pos += vec2{pos.x + (child->rect.x) + size.x - child->rect.w - padding_hor.x, pos.y + size.y -(child->rect.y) - child->rect.h - padding_vert.y};
    }
  }
}

void Canvas::show()
{
  is_visible = true;
}

void Canvas::hide()
{
  is_visible = false;
}

void Canvas::update(double dt)
{
  for (Object *child : children)
  {
    child->update(dt);
  }
}

void Canvas::draw()
{
  for (Object *child : children)
  {
    child->draw();
  }
}

void Canvas::dispose()
{
  for (Object *child : children)
  {
    child->dispose();
  }
}
