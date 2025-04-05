#include "Object.hpp"

class Rect_Object: public Object { 
public:
  Rect_Object(Rect rect, Col color, bool fill = true, bool border = false, int border_width = 1, Col border_color = {0, 0, 0, 255});
  ~Rect_Object();
  void awake() override;
  void start() override;
  void show() override;
  void hide() override;
  void update(double dt) override;
  void draw() override;
  void dispose() override;

private:
  Col color;
  bool fill;
  bool border;
  int border_width;
  Col border_color;
};
