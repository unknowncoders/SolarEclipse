#include "Transformation.h"

    Matrix Transformation::modelToWorld(const Vec3& preTranslation, float rotationAngle, const Vec3& postTranslation){

            Matrix transformationMatrix(4,4);

            Matrix preTranslationMatrix = Translate(preTranslation);
            Matrix rotationMatrix = RotateY(rotationAngle);
            Matrix postTranslationMatrix = Translate(postTranslation);

            transformationMatrix = postTranslationMatrix * rotationMatrix * preTranslationMatrix ;

            return transformationMatrix;

    }

   Matrix Transformation::worldToView(const Vec3& camera, const Vec3& lookTo){

        Matrix transformationMatrix(4,4);

        Vec3 N,U,V(0,1,0);

        N = camera-lookTo;
        N = N/ N.magnitude();

        U = V.crossProduct(N);
        U = U / U.magnitude();

        V = N.crossProduct(U);

        Matrix translation(4,4); 
        translation = Translate(Vec3(-1*camera.x, -1 * camera.y, -1 * camera.z));

        Matrix rotation(4,4);
        rotation = Rotation(U,V,N);
    
        transformationMatrix = rotation * translation;

        return transformationMatrix;

    }
   
    Matrix Transformation::Rotation(Vec3& U, Vec3& V, Vec3& N)
    {
    
       Matrix R(4,4);
       
        R(0,0) = U[0] ; R(0,1) = U[1]; R(0,2) = U[2]; R(0,3) = 0;
        R(1,0) = V[0] ; R(1,1) = V[1]; R(1,2) = V[2]; R(1,3) = 0;
        R(2,0) = N[0] ; R(2,1) = N[1]; R(2,2) = N[2]; R(2,3) = 0;
        R(3,0) = 0 ; R(3,1) = 0; R(3,2) = 0; R(3,3) = 1;
    
    
        return R;
    }
    
    Matrix Transformation::Translate(const Vec3& v)
    {
    
            Matrix temp(4,4);
    
             temp(0,0)=1.0f; temp(0,1)=0.0f; temp(0,2)=0.0f; temp(0,3)=v.x;
             temp(1,0)=0.0f; temp(1,1)=1.0f; temp(1,2)=0.0f; temp(1,3)=v.y;
             temp(2,0)=0.0f; temp(2,1)=0.0f; temp(2,2)=1.0f; temp(2,3)=v.z;
             temp(3,0)=0.0f; temp(3,1)=0.0f; temp(3,2)=0.0f; temp(3,3)=1.0f;
        
             return temp;
    
    }
    
    Matrix Transformation::Scale(float scale)
    {
    
            Matrix temp(4,4);
    
             temp(0,0)=scale; temp(0,1)=0.0f; temp(0,2)=0.0f; temp(0,3)=0;
             temp(1,0)=0.0f; temp(1,1)=scale; temp(1,2)=0.0f; temp(1,3)=0;
             temp(2,0)=0.0f; temp(2,1)=0.0f; temp(2,2)=scale; temp(2,3)=0;
             temp(3,0)=0.0f; temp(3,1)=0.0f; temp(3,2)=0.0f; temp(3,3)=1;
        
             return temp;
    
    
    
    }
    
    Matrix Transformation::Scale(const Vec3& v)
    {
    
            Matrix temp(4,4);
    
             temp(0,0)=v.x; temp(0,1)=0;    temp(0,2)=0;   temp(0,3)=0;
             temp(1,0)=0;   temp(1,1)=v.y;  temp(1,2)=0;   temp(1,3)=0;
             temp(2,0)=0;   temp(2,1)=0;    temp(2,2)=v.z; temp(2,3)=0;
             temp(3,0)=0;   temp(3,1)=0;    temp(3,2)=0;   temp(3,3)=1;
        
             return temp;
    
    }
    
    Matrix Transformation::RotateY(float angle)
    {
     
            angle = angle * 3.141592/180;
    
            Matrix temp(4,4);
             
             temp(0,0)=cosf(angle);  temp(0,1)=0;    temp(0,2)=sinf(angle); temp(0,3)=0;
             temp(1,0)=0;            temp(1,1)=1;    temp(1,2)=0;           temp(1,3)=0;
             temp(2,0)=-sinf(angle); temp(2,1)=0;    temp(2,2)=cosf(angle); temp(2,3)=0;
             temp(3,0)=0;            temp(3,1)=0;    temp(3,2)=0;           temp(3,3)=1;
        
             return temp;
    }
    
    Matrix Transformation::RotateX(float angle)
    {
     
            angle = angle * 3.141592/180;
    
            Matrix temp(4,4);
             
             temp(0,0)=1;  temp(0,1)=0;              temp(0,2)=0;             temp(0,3)=0;
             temp(1,0)=0;  temp(1,1)=cosf(angle);    temp(1,2)=-sinf(angle);  temp(1,3)=0;
             temp(2,0)=0;  temp(2,1)=sinf(angle);    temp(2,2)=cosf(angle);   temp(2,3)=0;
             temp(3,0)=0;  temp(3,1)=0;              temp(3,2)=0;             temp(3,3)=1;
        
             return temp;
    }
    
    
    Matrix Transformation::RotateZ(float angle)
    
    {
     
            angle = angle * 3.141592/180;
    
            Matrix temp(4,4);
             
             temp(0,0)=cosf(angle);  temp(0,1)=-sinf(angle); temp(0,2)=0;   temp(0,3)=0;
             temp(1,0)=sinf(angle);  temp(1,1)=cosf(angle);  temp(1,2)=0;   temp(1,3)=0;
             temp(2,0)=0;            temp(2,1)=0;            temp(2,2)=1;   temp(2,3)=0;
             temp(3,0)=0;            temp(3,1)=0;            temp(3,2)=0;   temp(3,3)=1;
        
             return temp;
    }
    
    
    Matrix Transformation::Perspective(float fov, float aspect, float near, float far)
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
    
    
    Matrix Transformation::Orthographic(float left, float right, float bottom, float top, float near, float far)
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
    
