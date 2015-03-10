#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

//#include <iostream>

#include "Vector.h"
#include "Matrix.h"


    class Transformation
    {
    
            public:
            
            Matrix modelToWorld(const Vec3& translation, float selfRotationAngle, float originRotationAngle);

            Matrix worldToView(const Vec3& camera, const Vec3& lookTo);

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

