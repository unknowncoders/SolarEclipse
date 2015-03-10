
#include <SDL/SDL.h>
#include <math.h>
#include "Graphics.h"
#include<iostream>
#include<algorithm>
#include <stdint.h>
#include "Vector.h"
#include "Object.h"

using namespace std;

int main(){
   
    Vec3 camera(0,0, 250);
    Vec3 LookTo(0,0, 0);
   
    Graphics G(1024,700);

    Object3d earth,moon;
 
    earth.LoadFile("resources/earth.bmp");    
    earth.LoadSphere(25, 150, 150);
    earth.mapcolor();
    
    moon.LoadSphere(5,50,50);
    moon.LoadFile("resources/earth.bmp");
    moon.mapcolor();

    SDL_Event event;
  
    float angle = 0;
    
    while (1)
    {
    
        G.clrscr();
        G.resetZ();

        earth.draw(&G,camera,LookTo,Vec3(0,0,0),Vec3(0,0,20),angle);
        moon.draw(&G,camera,LookTo,Vec3(0,0,-75),Vec3(0,0,75),angle);

        angle+=2;

        if(angle>360)
        angle= 0;
   
        while(SDL_PollEvent(&event))
            {
   
                    switch(event.type)
                {
            
                   case SDL_KEYDOWN:
                    switch (event.key.keysym.sym){
                       case SDLK_ESCAPE:
                               return 0;
                    }
                }
            }
        G.refresh();
    }
}


