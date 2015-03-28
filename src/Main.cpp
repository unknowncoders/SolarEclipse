
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

    Object3d earth,moon,star[10];
 
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

        star[0].setAttributes(Vec3(-140,50,-100),0,0);
        star[1].setAttributes(Vec3(150,-93,-100),0,0);
        star[2].setAttributes(Vec3(-140,140,-100),0,0);
        star[3].setAttributes(Vec3(-182,-119,-100),0,0);
        star[4].setAttributes(Vec3(62,90,-100),0,0);
        star[5].setAttributes(Vec3(-92,70,-100),0,0);
        star[6].setAttributes(Vec3(-132,-95,-100),0,0);
        star[7].setAttributes(Vec3(157,-138,-100),0,0);
        star[8].setAttributes(Vec3(-84,129,-100),0,0);
        star[9].setAttributes(Vec3(45,-90,-100),0,0);

    for(int i=0;i<10;i++){
        star[i].LoadSphere(1,6,6);
        star[i].mapsinglecolor();
        star[i].diffusionCoeff = 1.0;
        star[i].specularCoeff = 9.1;
        star[i].phongConstant = 4.1;
    }




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
        for(int i=0;i<10;i++)
        star[i].draw(&G,camera,LookTo);

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
             
                //while translate camera, star seems commedy
                /* 
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
                     */ 
                      case SDLK_ESCAPE:
                               return 0;
                    }
                }
            }
        G.refresh();
    }
}


