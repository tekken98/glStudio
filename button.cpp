#include "button.h"
#include <GL/gl.h>
#include "common.h"

 //BUTTON BEGIN

void Button::draw()
{
    if (!isRedraw())
        return ;
    clearRedraw();
    if (d_pressed )
    {
        drawDown();
    }
    else
        drawBevel(UI_COLOR_BEVEL_3,UI_COLOR_BEVEL_4,UI_COLOR_BEVEL_2,UI_COLOR_BEVEL_1);
    setGLColor(UI_COLOR_BUTTON);
    glRectf(x0+2, y0+2, x1-2, y1-2);
};

void Button::drawDown()
{
    drawBevel(UI_COLOR_BEVEL_2,UI_COLOR_BEVEL_1,UI_COLOR_BEVEL_3,UI_COLOR_BEVEL_4);
    setGLColor(UI_COLOR_BUTTON);
    glRectf(x0+2, y0+2, x1-2, y1-2);
}
Button& Button::operator=(const Button& s)
{
    return *this;
};

Button::Button(const Button& s)
{
};

void Button::moveWindow(int x,int y)
{
    x1 = x1 - x0 + x;
    y1 = y1 - y0 + y;
    x0 = x;
    y0 = y;
}
Button::Button()
{
};
 //BUTTON END

