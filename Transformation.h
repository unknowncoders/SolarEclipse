#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <iostream>
using namespace std;

#include "Vector.h"
#include "Matrix.h"


class Transform
{

public:

Vec3 cal_earth(const Vec3& source,float angle)
{

     Matrix temp(4,4), S(4,1);

     S(0) = source.x ; S(1) = source.y; S(2) = source.z ; S(3) = 1;

     Matrix T1 = Translate(Vec3(0,0, 20));

     Matrix R = RotateY(angle);
    
     temp = T1 * R;
     
     S = temp *  S;

     return Vec3(S(0), S(1), S(2));

}

Vec3 cal_moon(const Vec3& source,float angle)
{
    Matrix temp(4,4);

    Matrix S(4,1);   
    S(0) = source.x ; S(1) = source.y; S(2) = source.z ; S(3) = 1;

   
    Matrix T1 = Translate(Vec3(0,0,-75));

     Matrix R = RotateY(angle);
    
     Matrix T2 = Translate(Vec3(0,0,75));
  
     temp = T2 *  R * T1;
      
     S = temp * S;

     return Vec3(S(0), S(1), S(2));
}


Vec3 WtoV(const Vec3& source, const Vec3& camera, const Vec3& LookTo)
{

    Matrix WtoC(4,4);
   
    Vec3 N,U,V(0,1,0);
  
    Matrix S(4,1); //The source point in matrix form
   
    S(0) = source.x ; S(1) = source.y; S(2) = source.z ; S(3) = 1;
    
    N = camera-LookTo;
    N = N/ N.magnitude();

    U = V.crossProduct(N);
    U = U / U.magnitude();

    V = N.crossProduct(U);

   Matrix T(4,4); 

   T = Translate(Vec3(-1*camera.x, -1 * camera.y, -1 * camera.z));
   
   Matrix R(4,4);
   R = Rotation(U,V,N);


    WtoC = R*T;

      
    S = WtoC * S;

    Vec3 retVal;
    
    retVal.x = S(0);
    retVal.y = S(1);
    retVal.z = S(2);

    return retVal;
}

Vec3 VtoP(const Vec3& source)
{

   

    Matrix S(4,1); //The source point in matrix form
    S(0) = source.x ; S(1) = source.y; S(2) = source.z ; S(3) = 1;

    Matrix VtoP(4,4);

    VtoP =  Perspective(45,(float) 1024/700,0.01,10000);

    S = VtoP * S;

    Vec3 retVal;
    
    retVal.x = S(0)/S(3);
    retVal.y = S(1)/S(3);
    retVal.z = S(2)/S(3);
     return retVal;

}

Matrix Rotation(Vec3& U, Vec3& V, Vec3& N)
{

   Matrix R(4,4);
   
    R(0,0) = U[0] ; R(0,1) = U[1]; R(0,2) = U[2]; R(0,3) = 0;
    R(1,0) = V[0] ; R(1,1) = V[1]; R(1,2) = V[2]; R(1,3) = 0;
    R(2,0) = N[0] ; R(2,1) = N[1]; R(2,2) = N[2]; R(2,3) = 0;
    R(3,0) = 0 ; R(3,1) = 0; R(3,2) = 0; R(3,3) = 1;


    return R;
}

Matrix Translate(const Vec3& v)
{

        Matrix temp(4,4);

         temp(0,0)=1.0f; temp(0,1)=0.0f; temp(0,2)=0.0f; temp(0,3)=v.x;
         temp(1,0)=0.0f; temp(1,1)=1.0f; temp(1,2)=0.0f; temp(1,3)=v.y;
         temp(2,0)=0.0f; temp(2,1)=0.0f; temp(2,2)=1.0f; temp(2,3)=v.z;
         temp(3,0)=0.0f; temp(3,1)=0.0f; temp(3,2)=0.0f; temp(3,3)=1.0f;
    
         return temp;

}

Matrix Scale(float scale)
{

        Matrix temp(4,4);

         temp(0,0)=scale; temp(0,1)=0.0f; temp(0,2)=0.0f; temp(0,3)=0;
         temp(1,0)=0.0f; temp(1,1)=scale; temp(1,2)=0.0f; temp(1,3)=0;
         temp(2,0)=0.0f; temp(2,1)=0.0f; temp(2,2)=scale; temp(2,3)=0;
         temp(3,0)=0.0f; temp(3,1)=0.0f; temp(3,2)=0.0f; temp(3,3)=1;
    
         return temp;



}

Matrix Scale(const Vec3& v)
{

        Matrix temp(4,4);

         temp(0,0)=v.x; temp(0,1)=0;    temp(0,2)=0;   temp(0,3)=0;
         temp(1,0)=0;   temp(1,1)=v.y;  temp(1,2)=0;   temp(1,3)=0;
         temp(2,0)=0;   temp(2,1)=0;    temp(2,2)=v.z; temp(2,3)=0;
         temp(3,0)=0;   temp(3,1)=0;    temp(3,2)=0;   temp(3,3)=1;
    
         return temp;

}

Matrix RotateY(float angle)
{
 
        angle = angle * 3.141592/180;

        Matrix temp(4,4);
         
         temp(0,0)=cosf(angle);  temp(0,1)=0;    temp(0,2)=sinf(angle); temp(0,3)=0;
         temp(1,0)=0;            temp(1,1)=1;    temp(1,2)=0;           temp(1,3)=0;
         temp(2,0)=-sinf(angle); temp(2,1)=0;    temp(2,2)=cosf(angle); temp(2,3)=0;
         temp(3,0)=0;            temp(3,1)=0;    temp(3,2)=0;           temp(3,3)=1;
    
         return temp;
}

Matrix RotateX(float angle)
{
 
        angle = angle * 3.141592/180;

        Matrix temp(4,4);
         
         temp(0,0)=1;  temp(0,1)=0;              temp(0,2)=0;             temp(0,3)=0;
         temp(1,0)=0;  temp(1,1)=cosf(angle);    temp(1,2)=-sinf(angle);  temp(1,3)=0;
         temp(2,0)=0;  temp(2,1)=sinf(angle);    temp(2,2)=cosf(angle);   temp(2,3)=0;
         temp(3,0)=0;  temp(3,1)=0;              temp(3,2)=0;             temp(3,3)=1;
    
         return temp;
}


Matrix RotateZ(float angle)

{
 
        angle = angle * 3.141592/180;

        Matrix temp(4,4);
         
         temp(0,0)=cosf(angle);  temp(0,1)=-sinf(angle); temp(0,2)=0;   temp(0,3)=0;
         temp(1,0)=sinf(angle);  temp(1,1)=cosf(angle);  temp(1,2)=0;   temp(1,3)=0;
         temp(2,0)=0;            temp(2,1)=0;            temp(2,2)=1;   temp(2,3)=0;
         temp(3,0)=0;            temp(3,1)=0;            temp(3,2)=0;   temp(3,3)=1;
    
         return temp;
}


Matrix Perspective(float fov, float aspect, float near, float far)
{
    fov = fov * 3.141592/180;
    float temp = 1.0f / tanf(0.5f * fov);
    float d = 1.0f / (far - near);
    
    Matrix tem(4,4);

        tem(0,0)=temp/aspect; tem(0,1)=0.0f; tem(0,2)=0.0f;            tem(0,3)=0.0f;
        tem(1,0)=0.0f;        tem(1,1)=temp; tem(1,2)=0.0f;            tem(1,3)=0.0f;
        tem(2,0)=0.0f;        tem(2,1)=0.0f; tem(2,2)=-(far+near) * d; tem(2,3)=-(2*far*near)*d;
        tem(3,0)=0.0f;        tem(3,1)=0.0f; tem(3,2)=-1.0f;           tem(3,3)=0.0f;

    return tem;
}


Matrix Orthographic(float left, float right, float bottom, float top, float near, float far)

{
    float rl = 1.0f/(right - left);
    float tb = 1.0f/(top - bottom);
    float fn = 1.0f/(far - near);

    Matrix mat(4,4);

       mat(0,0)= 2*rl; mat(0,1)=0;    mat(0,2)= 0;     mat(0,3)= -(right+left)*rl;
       mat(1,0)=0;     mat(1,1)=2*tb; mat(1,2)= 0;     mat(1,3)= -(top+bottom)*tb;
       mat(2,0)=0;     mat(2,1)=0;    mat(2,2)= -2*fn; mat(2,3)= -(far+near)*fn;
       mat(3,0)=0;     mat(3,1)=0;    mat(3,2)= 0;     mat(3,3)= 1;

    return mat;
}
};

#endif

