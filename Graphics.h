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
        
            void operator = (const Color_uint& col)
            {
                 r = col.r;
                 g = col.g;
                 b = col.b;
            }
};


class Color{
    public:
        int  b, g, r;
    public: Color(){}
            Color(int rr, int gg, int bb):r(rr),g(gg),b(bb){}
        
            void operator = (const Color& col)
            {
                 r = col.r;
                 g = col.g;
                 b = col.b;
            }

            void operator = ( Color_uint& col)
            {
                 r =(int) col.r;
                 g =(int) col.g;
                 b =(int) col.b;
            }
  

};

class Vertex{

public:
     Vec3 vertices;
     Color color;
     Vec3 normals;
     Vec2 texcoords;

    void operator = (const Vertex& v)
            {
                 vertices = v.vertices;
                 color = v.color;
                 normals  = v.normals;
                 texcoords = v.texcoords;
            }
};

class Graphics{
    SDL_Surface* screen;
    float *Zbuffer;
    
   public:
        Graphics(int width = 1024,int height=600){
            SDL_Init(SDL_INIT_EVERYTHING);
            screen = SDL_SetVideoMode(width,height,32,SDL_SWSURFACE);
            Zbuffer = new float[(width*height)];
        }

        void setpixel(Vec3 P,Color c);
    
        void setpixel(int x,int y,float z,  Color c){
            Vec3 temp(x,y,z);
            setpixel(temp,c);
        }
        void line(Vertex P1,Vertex P2);

        bool WaitQuit();

        void refresh(){
            SDL_Flip(screen);
        }

        void clrscr(){
            SDL_Rect R;
            R.x =0; R.y =0;
            R.h = screen->h; R.w = screen->w;
            SDL_FillRect(screen,&R,0);
        
        }

        void resetZ()
        {
           delete[] Zbuffer;
          
           Zbuffer = new float[(screen->w)*(screen->h)];
           
           fill_n(Zbuffer,(screen->w)*(screen->h),100);

        }
 
      //to fill the triangle
        void fill_bottom_flat_triangle(Vertex , Vertex, Vertex);
        
        void fill_top_flat_triangle(Vertex , Vertex, Vertex );
       
        void fill_all_triangle(Vertex , Vertex , Vertex);


        ~Graphics()
        {
           
         if(screen)
         {
           SDL_FreeSurface(screen);
           screen = NULL;
         }
                SDL_Quit();
                delete[] Zbuffer;
        }
};



#endif // GRAPHICS_H_

