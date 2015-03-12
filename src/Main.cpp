
#include <SDL/SDL.h>
#include <math.h>
#include "Graphics.h"
#include<iostream>
#include<algorithm>
#include <stdint.h>
#include "Vector.h"
#include "Object.h"


int main(){
   
    Vec3 camera(0,0, 250);
    Vec3 LookTo(0,0, 0);
   
    Graphics G(1024,700);
    G.ambientCoeff = 1.0f;
    G.setlightcolor(Vec3(0.75,0.75,0.75));

    Object3d earth,moon;
 
    earth.LoadFile("resources/earth.bmp");    
    earth.LoadSphere(25, 150, 150);
    earth.mapcolor();
    earth.setAttributes(Vec3(0,0,0),0,0);
    
    moon.LoadSphere(5,50,50);
    moon.LoadFile("resources/earth.bmp");
    moon.mapcolor();
    moon.setAttributes(Vec3(0,0,-90),0,0);


    SDL_Event event;
  
    float angle = 0;
    float angle1 = 0;
    
    while (1)
    {
    
        G.clrscr();
        G.resetZ();

        earth.draw(&G,camera,LookTo);
        moon.draw(&G,camera,LookTo);
        earth.setAngles(angle,0);
        moon.setAngles(0,angle1);

        angle+=2;
        angle1+=1;

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


