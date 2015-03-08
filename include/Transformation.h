#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <iostream>
using namespace std;

#include "Vector.h"
#include "Matrix.h"


    class Transformation
    {
    
            public:
            
            Vec3 cal_earth(const Vec3& source,float angle);
            
            Vec3 cal_moon(const Vec3& source,float angle);
            
            Vec3 WtoV(const Vec3& source, const Vec3& camera, const Vec3& LookTo);
            
            Vec3 VtoP(const Vec3& source);
            
            Matrix Rotation(Vec3& U, Vec3& V, Vec3& N);
            
            Matrix Translate(const Vec3& v);
            
            Matrix Scale(float scale);
            
            Matrix Scale(const Vec3& v);
            
            Matrix RotateY(float angle);
            
            Matrix RotateX(float angle);
            
            Matrix RotateZ(float angle);
            
            Matrix Perspective(float fov, float aspect, float near, float far);
            
            Matrix Orthographic(float left, float right, float bottom, float top, float near, float far);
            
    };

#endif

