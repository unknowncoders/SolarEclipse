
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

    Object3d obj1,obj2;
 
    obj1.LoadFile("resources/earth.bmp");    
    obj1.LoadSphere(25, 150, 150);
    obj1.mapcolor();
    
    obj2.LoadSphere(10,50,50);
    obj2.LoadFile("resources/earth.bmp");
    obj2.mapcolor();

    SDL_Event event;
  
    float angle = 0;
    
    while (1)
    {
    
        G.clrscr();
        G.resetZ();

        obj1.drawearth(&G,camera,LookTo,angle);
        obj2.drawmoon(&G,camera,LookTo,angle);

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


