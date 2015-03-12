#include "Object.h"

    void Object3d::LoadFile(std::string filename)
    {
            std::ifstream file;
            file.open(filename.c_str());
     
            if (file.is_open())
            {
                uint32_t sizeFile, offset;
                file.seekg(0, std::ios::beg);
                file.seekg(2);
                file.read((char*)&sizeFile, sizeof(sizeFile));
                file.seekg(10);
                file.read((char*)&offset, sizeof(offset));
                file.seekg(18);
                file.read((char*)&width, sizeof(width));
                file.seekg(22);
                file.read((char*)&height, sizeof(height));
                
                if (width > 0 && height > 0)
                {
                    pixels.resize(width*height);
                    file.seekg(offset);
                    file.read((char*)&pixels[0], sizeof(Color)*width*height);
                }
    
                file.close();
            }
            else
                std::cout << "Couldn't load texture: " << filename << std::endl;
     
    }
    
    #define Min(a,b) (a<b?a:b)
    
    Color_uint& Object3d::Sample(float u, float v)
        {
            uint32_t x = uint32_t(u*((float)width-1));
            uint32_t y = uint32_t(v*((float)height-1));
            x = Min(x, width-1);
            y = Min(y, height-1);
            return pixels[y*width + x];
        }
    
    
    Color_uint& Object3d::Sample(const Vec2& v)
        {
            return Sample(v.x, v.y);
        }
    
    
    void Object3d::LoadSphere(float radius, uint16_t rings, uint16_t sectors)
    {
        float R = 1.0f / float(rings-1);
        float S = 1.0f / float(sectors-1);
        uint16_t r, s;
    
        m_vertices.resize(rings*sectors);
    
        int i=0;

        for (r=0; r<rings; ++r){
            for (s=0; s<sectors; ++s)
            {
      
                   #define PI (3.14159265359f)
                   #define PI_2 (1.57079632679f)
      
                float y = -sinf(-PI_2 + PI * r * R);
                float x = cosf(2 * PI * s * S) * sinf(PI * r * R);
                float z = sinf(2 * PI * s * S) * sinf(PI * r * R);
    
                m_vertices[i].texcoords.x = s*S;
                m_vertices[i].texcoords.y = r*R;
    
                m_vertices[i].vertices.x = x*radius;
                m_vertices[i].vertices.y = y*radius;
                m_vertices[i].vertices.z = z*radius;
                
                m_vertices[i].normals.x = x;
                m_vertices[i].normals.y = y;
                m_vertices[i].normals.z = z;
                ++i;
            }
        }
    
        m_indices.resize((rings-1)*(sectors-1)*6);
       
        uint16_t* id = &m_indices[0];
       
        for (r=0; r<rings-1; ++r){
            for (s=0; s<sectors-1; ++s)
            {
                *id++ = uint16_t(r*sectors + s);
                *id++ = uint16_t(r*sectors + s+1);
                *id++ = uint16_t((r+1)*sectors + s+1);
                *id++ = uint16_t(r*sectors + s);
                *id++ = uint16_t((r+1)*sectors + s+1);
                *id++ = uint16_t((r+1)*sectors + s);
            }
        }
        
    }
    
    void Object3d::setAttributes(Vec3 _pos , float _selfRotAngle, float _originRotAngle){

            position = _pos;
            selfRotationAngle = _selfRotAngle;
            originRotationAngle = _originRotAngle;

    }

    void Object3d::setAngles(float _selfRotAngle, float _originRotAngle){

            selfRotationAngle = _selfRotAngle;
            originRotationAngle = _originRotAngle;
            
    }

    void Object3d::mapcolor()
    {
        
        for(unsigned int i=0;i<m_vertices.size();i++)
        {
           m_vertices[i].color =   Sample(m_vertices[i].texcoords);   
        }
    
    
    }
    
    int Object3d::DecreaseIntensity(int _val, int _margin){
       int ret = _val - _margin;
       if(ret < 0) return 0;

       return ret;
    }

    void Object3d::draw(Graphics *G, Vec3& camera, Vec3& LookTo){

        unsigned int len = m_vertices.size();
    
        Vertex v[len];

        Matrix modelToWorldMat(4,4),worldToViewMat(4,4),projectionMat(4,4);

        modelToWorldMat = T.modelToWorld(position, selfRotationAngle, originRotationAngle);
        worldToViewMat = T.worldToView(camera,LookTo);
        projectionMat = T.Perspective(45,(float) 1024/700,0.01,10000);

        Matrix compositeTransformation(4,4);
        compositeTransformation = projectionMat * worldToViewMat * modelToWorldMat;

        for (unsigned int i=0;i<len;i++){

                v[i] =  m_vertices[i];

                Matrix vertexMat(4,1);

                vertexMat(0) = v[i].vertices.x;
                vertexMat(1) = v[i].vertices.y;
                vertexMat(2) = v[i].vertices.z;
                vertexMat(3) = 1 ;

                vertexMat = compositeTransformation * vertexMat;


                v[i].vertices = Vec3(vertexMat(0)/vertexMat(3),vertexMat(1)/vertexMat(3),vertexMat(2)/vertexMat(3));

                v[i].vertices.x =(v[i].vertices.x*0.5f+0.5f)*1024;
                v[i].vertices.y =(v[i].vertices.y*0.5f+0.5f)*700;

                v[i].color.r *= G->lightColor.x * G->ambientCoeff ;
                v[i].color.g *= G->lightColor.y * G->ambientCoeff ;
                v[i].color.b *= G->lightColor.z * G->ambientCoeff ;


        }

        for(unsigned int i=0;i<m_indices.size();i+=3)
               G->fill_all_triangle(v[m_indices[i]],v[m_indices[i+1]], v[m_indices[i+2]]);

    }

   
