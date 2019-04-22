#ifndef BUTTON_H
#define BUTTON_H
#include "object.h"
class Button:public Object{
    private:
    public:
        //constructor
        Button();
        Button(const Button& s);
        Button& operator=(const Button& s);
        ~Button(){};
        virtual void draw();
    public:
        virtual void drawDown();
        void moveWindow(int x , int y);
        //maniulator
        //accessor
}; 
#endif
