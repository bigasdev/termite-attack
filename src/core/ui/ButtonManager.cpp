#include "ButtonManager.hpp"

#include "../../entity/ui/Button.hpp"
#include "../../tools/Mouse.hpp"
#include "../../core/global.hpp"

ButtonManager::ButtonManager() {}

ButtonManager::~ButtonManager() {
  for (Button* button : buttons) {
    delete button;
  }
}

void ButtonManager::add_button(Button* button) {
  buttons.push_back(button);
  button->on_enable();
}

void ButtonManager::remove_button(std::string name) {
  for (int i = 0; i < buttons.size(); i++) {
    if (buttons[i]->name == name) {
      buttons[i]->on_disable();
      buttons.erase(buttons.begin() + i);
      return;
    }
  }
}

void ButtonManager::update(double dt) {
  for (Button* button : buttons) {
    button->update(dt);

    if(Mouse::is_at_area(button->get_click_area())){
      button->on_hover();
      if(Mouse::is_clicked){
        button->on_click();
        Mouse::is_clicked = false;
      }
    } else {
      button->on_leave();
    }
  }
}

void ButtonManager::draw() {
  for (Button* button : buttons) {
    //button->draw();
  }
}
