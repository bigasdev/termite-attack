#pragma once

#include <string>
#include <vector>

class Button;

class ButtonManager
{
public:
  ButtonManager();
  ~ButtonManager();

  void add_button(Button* button);
  void remove_button(std::string name);
  void update(double dt);
  void draw();

private:
  std::vector<Button*> buttons;
};


