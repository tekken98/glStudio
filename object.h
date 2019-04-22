#ifndef OBJECT_H
#define OBJECT_H
#include <iostream>
using namespace std;
class Object{
    protected:
        int x0,y0;
        int x1,y1;
        bool d_pressed;
        bool d_redraw;
        //constructor
        Object(const Object& s);
        Object& operator=(const Object& s);
    public:
        Object();
        ~Object(){};
        //maniulator
        virtual void drawDown(){};
        virtual void moveWindow(int x , int y){};
        virtual void draw(){};
        virtual void setRedraw(){
            d_redraw = true;
        }
        virtual void clearRedraw(){
            d_redraw = false;
        }
        virtual void setPressed() { d_pressed = true;setRedraw();}
        virtual void clearPressed(){d_pressed =false;setRedraw();};
        virtual bool isRedraw(){ return d_redraw == true;};
        void drawBevel(unsigned ,unsigned ,unsigned,unsigned);
        //accessor
        virtual bool ptIn(int x , int y);
        virtual void getSize(int &w, int & h)
        { 
            w = x1 - x0;
            h = y1 - y0;
        };
        //other
        void setGLColor(unsigned int);
}; 
#endif
