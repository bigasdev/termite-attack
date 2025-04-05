#pragma once 

#include <vector>
#include "../../tools/Common.hpp"

class Object
{
public:
    virtual ~Object(){}
    virtual void awake() = 0;
    virtual void start() = 0;
    virtual void show() = 0;
    virtual void hide() = 0;
    virtual void update(double dt) = 0;
    virtual void draw() = 0;
    virtual void dispose() = 0;

    virtual vec2 get_pos(){
      if(parent != nullptr){
        return parent->get_pos() + pos;
      }
      return pos;
    }

    virtual void set_parent(Object* parent) {
        this->parent = parent;

        if (parent != nullptr) {
            parent->children.push_back(this);
        }
    }

    Object *parent = nullptr;
    std::vector<Object*> children;

    vec2 pos;
    Rect rect;

    bool is_visible = true;
};

