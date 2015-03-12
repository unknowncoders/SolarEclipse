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

//using namespace std;

    class Object3d{
    
        private:
       
                Transformation T;
    
                uint32_t width, height;
                std::vector<Color_uint> pixels; 
    
                std::vector<Vertex> m_vertices;     // Vertex Buffer
                std::vector<uint16_t> m_indices;    // Index Buffer

                float selfRotationAngle;
                float originRotationAngle;
                Vec3 position;
    
        public:

            float diffusionCoeff;
          
            Color_uint& Sample(float u, float v);
            Color_uint& Sample(const Vec2& v);
    
           
            void mapcolor();
            void LoadSphere(float radius, uint16_t rings, uint16_t sectors);
            void LoadFile(std::string filename);
            void setAttributes(Vec3 _pos , float _selfRotAngle, float _originRotAngle);
            void setAngles(float _selfRotAngle, float _originRotAngle);

            float lowerLimitZero(float _val);
            void draw(Graphics *G, Vec3& camera,Vec3& LookTo);
            int DecreaseIntensity(int _val,int _margin);
    };



#endif // OBJECT_H_

