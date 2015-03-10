#ifndef OBJECT_H_
#define OBJECT_H_

#include "Graphics.h"
#include "Matrix.h"
#include "Vector.h"
#include "Transformation.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>

using namespace std;

    class Object3d{
    
        private:
       
                Transformation T;
    
                uint32_t width, height;
                vector<Color_uint> pixels; 
    
                vector<Vertex> m_vertices;     // Vertex Buffer
                vector<uint16_t> m_indices;    // Index Buffer
    
        public:
          
            Color_uint& Sample(float u, float v);
            Color_uint& Sample(const Vec2& v);
    
            void draw(Graphics *G, Vec3& camera,Vec3& LookTo,Vec3 preTranslation, Vec3 postTranslation,float angle);
           
            void LoadObject(string filename);

            int DecreaseIntensity(int _val,int _margin);
            
            void mapcolor();
            void LoadSphere(float radius, uint16_t rings, uint16_t sectors);
            void LoadFile(string filename);
    };



#endif // OBJECT_H_

