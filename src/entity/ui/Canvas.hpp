#include "Object.hpp"

enum CanvasAlignment
{
    TOP_LEFT,
    TOP_CENTER,
    TOP_RIGHT,
    CENTER_LEFT,
    CENTER,
    CENTER_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_CENTER,
    BOTTOM_RIGHT
};

class Canvas : public Object
{
public:
    Canvas(vec2 size = vec2{0, 0}, vec2 padding_vert = vec2{0, 0}, vec2 padding_hor = vec2{0, 0}, Col background_color = {0, 0, 0, 0});
    ~Canvas();

    void awake() override;
    void start() override;
    void show() override;
    void hide() override;
    void update(double dt) override;
    void draw() override;
    void dispose() override;

    void set_alignment(CanvasAlignment alignment) { this->alignment = alignment; }

private:
    CanvasAlignment alignment = TOP_LEFT;
    vec2 size;
    vec2 padding_vert;
    vec2 padding_hor;
    Col background_color;
};
