
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
    G.ambientCoeff = 0.0f;
    G.setlightcolor(Vec3(0.7,0.7,0.7));
    G.setlightvector(Vec3(-1.0,0.0,0.0));

    Object3d earth,moon;
 
    earth.LoadFile("resources/earthTexture.bmp");    
    earth.LoadSphere(25, 158, 158);
    earth.mapcolor();
    earth.setAttributes(Vec3(0,0,0),0,0);
    earth.diffusionCoeff = 1.0;
    earth.specularCoeff = 0.2;
    earth.phongConstant = 0.1;
    
    moon.LoadSphere(10,65,65);
    moon.LoadFile("resources/moonTexture.bmp");
    moon.mapcolor();
    moon.setAttributes(Vec3(-90,0,0),0,0);
    moon.diffusionCoeff = 1.0;
    moon.specularCoeff = 0.2;
    moon.phongConstant = 0.1;


    SDL_Event event;
  
    float angle = 0;
    float angle1 = 0;

    
    while (1)
    {
    
        G.clrscr();
        G.resetZ();
        G.resetLightBuffer();

        moon.drawToLight(&G);
        earth.drawToLight(&G);

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
               
                      case SDLK_LEFT:
                              camera.x-=10; 
                              std::cout<<camera.x<<std::endl;  
                              break;

                      case SDLK_RIGHT:
                             camera.x+=10;
                              std::cout<<camera.x<<std::endl;  
                              break; 
                
                      case SDLK_DOWN:
                              camera.z-=10; 
                              std::cout<<camera.z<<std::endl;  
                              break;

                      case SDLK_UP:
                             camera.z+=10;
                              std::cout<<camera.z<<std::endl;  
                              break; 
                      
                      case SDLK_ESCAPE:
                               return 0;
                    }
                }
            }
        G.refresh();
    }
}


