#ifndef GRAPHICS_H_
#define GRAPHICS_H_


#include <SDL/SDL.h>
#include <math.h>
#include "Vector.h"
#include<iostream>
#include<algorithm>
#include <stdint.h>
using namespace std;

#define round(a) ((int) (a+0.5))

    class Color_uint{
        public:
            uint8_t b, g, r;
        public: Color_uint(){}
                Color_uint(int rr, int gg, int bb):r(rr),g(gg),b(bb){}
            
                void operator = (const Color_uint& col);
    };
    
    
    class Color{
        public:
            int  b, g, r;
        public: Color(){}
                Color(int rr, int gg, int bb):r(rr),g(gg),b(bb){}
            
                void operator = (const Color& col);
    
                void operator = ( Color_uint& col);
    
    };
    
    class Vertex{
    
        public:
             Vec3 vertices;
             Color color;
             Vec3 normals;
             Vec2 texcoords;
        
            void operator = (const Vertex& v);
    };
    
    class Graphics{
       private:
        SDL_Surface* screen;
        float *Zbuffer;
        
       public:
            Graphics(int width = 1024,int height=600);
    
            void setpixel(Vec3 P,Color c);
        
            void setpixel(int x,int y,float z,  Color c);
    
            void line(Vertex P1,Vertex P2);
    
            bool WaitQuit();
    
            void refresh();
    
            void clrscr();
    
            void resetZ();
     
          //to fill the triangle
            void fill_bottom_flat_triangle(Vertex , Vertex, Vertex);
            
            void fill_top_flat_triangle(Vertex , Vertex, Vertex );
           
            void fill_all_triangle(Vertex , Vertex , Vertex);
    
    
            ~Graphics();
    };
    


#endif // GRAPHICS_H_

