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

    float Object3d::lowerLimitZero(float _val){

            if(_val < 0 )
                    return 0;

            return _val;

    }

    void Object3d::printVal(){
            for(int i=0;i<m_vertices.size();i=i+3){
                    std::cout<<m_vertices[m_indices[i]].vertices.x<<":"<<m_vertices[m_indices[i]].vertices.y<<":"<<m_vertices[m_indices[i]].vertices.z<<std::endl;
                    std::cout<<m_vertices[m_indices[i+1]].vertices.x<<":"<<m_vertices[m_indices[i+1]].vertices.y<<":"<<m_vertices[m_indices[i+1]].vertices.z<<std::endl;
                    std::cout<<m_vertices[m_indices[i+2]].vertices.x<<":"<<m_vertices[m_indices[i+2]].vertices.y<<":"<<m_vertices[m_indices[i+2]].vertices.z<<std::endl;
            }
    }

    void Object3d::draw(Graphics *G, Vec3& camera, Vec3& LookTo){

        unsigned int len = m_vertices.size();
    
        Vertex v[len];

        Matrix modelToWorldMat(4,4),worldToViewMat(4,4),projectionMat(4,4),normalRotationMat(4,4);


        modelToWorldMat = T.modelToWorld(position, selfRotationAngle, originRotationAngle);
        worldToViewMat = T.worldToView(camera,LookTo);
        projectionMat = T.Perspective(45,(float) 1024/700,0.01,10000);

        normalRotationMat = T.modelToWorld(position, selfRotationAngle + originRotationAngle, 0.0);

        Vec3 cameraVector = camera - LookTo ;
        cameraVector = cameraVector/cameraVector.magnitude();
        Vec3 halfwayVector = cameraVector + G->lightVector;
        halfwayVector = halfwayVector/halfwayVector.magnitude();


        Matrix compositeTransformation(4,4);
        compositeTransformation = projectionMat * worldToViewMat * modelToWorldMat;

        for (unsigned int i=0;i<len;i++){

                v[i] =  m_vertices[i];

                v[i].visible = true;

                Matrix vertexMat(4,1),normalMat(4,1);
                
                normalMat(0) = v[i].normals.x;
                normalMat(1) = v[i].normals.y;
                normalMat(2) = v[i].normals.z;
                normalMat(3) = 1;

                normalMat = normalRotationMat * normalMat;

                v[i].normals = Vec3(normalMat(0),normalMat(1),normalMat(2));
                v[i].normals = v[i].normals/v[i].normals.magnitude();
                        

                vertexMat(0) = v[i].vertices.x;
                vertexMat(1) = v[i].vertices.y;
                vertexMat(2) = v[i].vertices.z;
                vertexMat(3) = 1 ;

                vertexMat = compositeTransformation * vertexMat;


                v[i].vertices = Vec3(vertexMat(0)/vertexMat(3),vertexMat(1)/vertexMat(3),vertexMat(2)/vertexMat(3));

                //v[i].vertices.x =(v[i].vertices.x*0.5f+0.5f)*1024;
                //v[i].vertices.y =(v[i].vertices.y*0.5f+0.5f)*700;

                /*

                if(v[i].normals.dotProduct(cameraVector)>0){
                        if(i==0){
                         std::cout<<i<<"="<<v[i].normals.x<<":"<<v[i].normals.y<<":"<<v[i].normals.z;

                         std::cout<<i<<"="<<cameraVector.x<<":"<<cameraVector.y<<":"<<cameraVector.z;
                        }
                        v[i].visible = false;
                        continue;
                }
                */


                float diffusionFactor = diffusionCoeff * lowerLimitZero(v[i].normals.dotProduct(G->lightVector));
                float specularFactor = specularCoeff * pow(lowerLimitZero(v[i].normals.dotProduct(halfwayVector)),phongConstant);

                //TODO Fix whether to use the lightColor or vertexColor or a dedicated color for the specular lighting
                v[i].color.r = G->lightColor.x * G->ambientCoeff * v[i].color.r + v[i].color.r * diffusionFactor + specularFactor * G->lightColor.x;
                v[i].color.g = G->lightColor.y * G->ambientCoeff * v[i].color.g + v[i].color.g * diffusionFactor + specularFactor * G->lightColor.y;
                v[i].color.b = G->lightColor.z * G->ambientCoeff * v[i].color.b + v[i].color.b * diffusionFactor + specularFactor * G->lightColor.z;



        }

        for(unsigned int i=0;i<m_indices.size();i+=3){
                Vertex v1 = v[m_indices[i]];
                Vertex v2 = v[m_indices[i+1]];
                Vertex v3 = v[m_indices[i+2]];

                /*
                    v1 and v2 produces same value! 
                    TODO figure out why this is happening.

                if(i==0){
                    std::cout<<v1.vertices.x<<":"<<v1.vertices.y<<":"<<v1.vertices.z<<std::endl;
                    std::cout<<v2.vertices.x<<":"<<v2.vertices.y<<":"<<v2.vertices.z<<std::endl;
                    std::cout<<v3.vertices.x<<":"<<v3.vertices.y<<":"<<v3.vertices.z<<std::endl;
                }

                */
                
                Vec3 v12 = v1.vertices - v2.vertices;
                Vec3 v23 = v2.vertices - v3.vertices;

                Vec3 normal = v12.crossProduct(v23);

                normal = normal/normal.magnitude();

                //Main Culling point. If the surface is facing away. Don't draw it. Just continue

                if(normal.dotProduct(cameraVector) < 0){
                        continue;
                }

            //if(v[m_indices[i]].visible && v[m_indices[i+1]].visible && v[m_indices[i+2]].visible)
                v1.vertices.x =(v1.vertices.x*0.5f+0.5f)*1024;
                v1.vertices.y =(v1.vertices.y*0.5f+0.5f)*700;

                v2.vertices.x =(v2.vertices.x*0.5f+0.5f)*1024;
                v2.vertices.y =(v2.vertices.y*0.5f+0.5f)*700;

                v3.vertices.x =(v3.vertices.x*0.5f+0.5f)*1024;
                v3.vertices.y =(v3.vertices.y*0.5f+0.5f)*700;

               //G->fill_all_triangle(v[m_indices[i]],v[m_indices[i+1]], v[m_indices[i+2]]);
               G->fill_all_triangle(v1,v2, v3);
        }

    }

   
