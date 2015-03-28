#include "Matrix.h"
#include "Vector.h"
#include "Graphics.h"

    /* Color_uint ---------------------------------------------*/ 
    
    void Color_uint::operator = (const Color_uint& col)
    {
                     r = col.r;
                     g = col.g;
                     b = col.b;
    }
    
    /*---------------------------------------------------------*/
    
    /* Color ---------------------------------------------*/ 
    
    void Color::operator = (const Color& col)
    {
         r = col.r;
         g = col.g;
         b = col.b;
    }
    
    
    void Color::operator = ( Color_uint& col)
    {
         r =(int) col.r;
         g =(int) col.g;
         b =(int) col.b;
    }
    
    /*---------------------------------------------------------*/
    
    /* Vertex ---------------------------------------------*/ 
    
    void Vertex::operator = (const Vertex& v)
    {
         vertices = v.vertices;
         color = v.color;
         normals  = v.normals;
         texcoords = v.texcoords;
    }
    
    /*---------------------------------------------------------*/
    
    /* Graphics ---------------------------------------------*/ 
    
    Graphics::Graphics(int width, int height){
    
        SDL_Init(SDL_INIT_EVERYTHING);
        screen = SDL_SetVideoMode(width,height,32,SDL_SWSURFACE);
        Zbuffer = new float[(width*height)];
        lightBuffer = new float[(width * height)];
    
    }
    
    Graphics::~Graphics(){
               
             if(screen)
             {
               SDL_FreeSurface(screen);
               screen = NULL;
             }
                    SDL_Quit();
                    delete[] Zbuffer;
    }
    
    void Graphics::setlightcolor(Vec3 _lightColor){
            
            lightColor = _lightColor;

    }

    void Graphics::printLightBuffer(){

            for(int x = 482; x<= 542 ; x++){
                for(int y = 320; y<= 380;y++){

                        int val = lightBuffer[x*700+y];
                        std::cout<<x<<","<<y<<"=>"<<val<<":";

                }
                std::cout<<std::endl;
            }

    }
    
    void Graphics::setlightvector(Vec3 _lightVector){

            lightVector = _lightVector;

    }

    void  Graphics::fill_all_triangle(Vertex v1, Vertex v2, Vertex v3)
    {
  
                   Vertex v[3];
                    v[0] = v1;
                    v[1] = v2;
                    v[2] = v3;
            
            //arranging the vertices in ascending order
            
            
                 for(int i = 0; i<2; i++){
                    for(int j =i+1; j< 3; j++)
                    {
                         if(v[i].vertices.y>v[j].vertices.y)
                         {
                            Vertex temp; 
                              temp = v[i];
                              v[i] = v[j];
                              v[j] = temp;
                         }
                            
                    }
                 }
            
            
            if(v[0].vertices.y==v[1].vertices.y)
            {
            
                fill_bottom_flat_triangle ( v[2] , v[0], v[1]) ;
            
            }
            
            else if(v[1].vertices.y==v[2].vertices.y)
            {
            
                fill_top_flat_triangle( v[0], v[1], v[2]);
            }
            else
            {
            
                Vertex v4;
                
                v4.vertices.x = v[0].vertices.x + ((v[2].vertices.x-v[0].vertices.x)*(v[1].vertices.y-v[0].vertices.y))/(v[2].vertices.y-v[0].vertices.y);
                v4.vertices.y = v[1].vertices.y;
                v4.vertices.z = v[0].vertices.z + ((v[2].vertices.z-v[0].vertices.z)*(v[1].vertices.y-v[0].vertices.y))/(v[2].vertices.y-v[0].vertices.y);
                
                v4.color.r = (v[0].color.r + v[1].color.r + v[2].color.r)/3;
                v4.color.g = (v[0].color.g + v[1].color.g + v[2].color.g)/3;
                v4.color.b = (v[0].color.b + v[1].color.b + v[2].color.b)/3;
                
                fill_bottom_flat_triangle(v[2] , v4, v[1]);
                
                fill_top_flat_triangle( v[0], v[1], v4);
            
            }
    
    }
    
    void Graphics::fill_bottom_flat_triangle(Vertex v1 , Vertex v2, Vertex v3)
    {
  
           Vertex t1, t2;
    
           t1 =  v1;
           t2 =  v1;
           
           float m1 = (v2.vertices.y-v1.vertices.y)/( v2.vertices.x-v1.vertices.x);
           float m2 = (v3.vertices.y-v1.vertices.y)/( v3.vertices.x-v1.vertices.x);
       
           float z1 = (v2.vertices.y-v1.vertices.y)/( v2.vertices.z-v1.vertices.z);
           float z2 = (v3.vertices.y-v1.vertices.y)/( v3.vertices.z-v1.vertices.z);
     
           float r1 = (v2.vertices.y-v1.vertices.y)/( v2.color.r-v1.color.r);
           float r2 = (v3.vertices.y-v1.vertices.y)/( v3.color.r-v1.color.r);
            
           float g1 = (v2.vertices.y-v1.vertices.y)/( v2.color.g-v1.color.g);
           float g2 = (v3.vertices.y-v1.vertices.y)/( v3.color.g-v1.color.g);
               
           float b1 = (v2.vertices.y-v1.vertices.y)/( v2.color.b-v1.color.b);
           float b2 = (v3.vertices.y-v1.vertices.y)/( v3.color.b-v1.color.b);
  
    /* 
         if(m1 == 0) 
           std::cout<<"M1 is zero"<<std::endl;
         if(m2 == 0)
            std::cout<<"M2 is 0"<<std::endl;
           
         if(z1 == 0) 
           std::cout<<"z1 is zero"<<std::endl;
         if(z2 == 0)
            std::cout<<"z2 is 0"<<std::endl;
           
         if(r1 == 0) 
           std::cout<<"r1 is zero"<<std::endl;
         if(r2 == 0)
            std::cout<<"r2 is 0"<<std::endl;
           
         if(g1 == 0) 
           std::cout<<"g1 is zero"<<std::endl;
        if(g2 == 0)
            std::cout<<"g2 is 0"<<std::endl;
        if(b1 == 0) 
           std::cout<<"b1 is zero"<<std::endl;
        if(b2 == 0)
            std::cout<<"b2 is 0"<<std::endl;
       
        
        int infinte = 100000000; 
       
        if(1/m1 == 0) 
           m1 = infinte;

         if(1/m2 == 0)
           m2 = infinte;
      
        if(1/z1 == 0) 
           z1 = infinte;
       
        if(1/z2 == 0)
           z2 = infinte;
           
         if(1/r1 == 0) 
           r1 = infinte;
        
         if(1/r2 == 0)
           r2 = infinte;
           
         if(1/g1 == 0) 
           g1 = infinte;
        
         if(1/g2 == 0)
           g2 = infinte;
        
         if(1/b1 == 0) 
           b1 = infinte;
        
         if(1/b2 == 0)
           b2 = infinte;
*/
           while(t1.vertices.y >=v2.vertices.y)
           
           {
          
                t1.vertices.x  = v1.vertices.x + (t1.vertices.y - v1.vertices.y)/m1;
                t1.vertices.z  = v1.vertices.z + (t1.vertices.y - v1.vertices.y)/z1;
          
                t2.vertices.x  = v1.vertices.x + (t2.vertices.y - v1.vertices.y)/m2;
                t2.vertices.z  = v1.vertices.z + (t2.vertices.y - v1.vertices.y)/z2;
    
    
                t1.color.r  = v1.color.r + (t1.vertices.y - v1.vertices.y)/r1;
                t2.color.r  = v1.color.r + (t2.vertices.y - v1.vertices.y)/r2;
    
    
                t1.color.g  = v1.color.g + (t1.vertices.y - v1.vertices.y)/g1;
                t2.color.g  = v1.color.g + (t2.vertices.y - v1.vertices.y)/g2;
    
    
                t1.color.b  = v1.color.b + (t1.vertices.y - v1.vertices.y)/b1;
                t2.color.b  = v1.color.b + (t2.vertices.y - v1.vertices.y)/b2;
    
                
                line(t1,t2);
                
                t1.vertices.y--;
                t2.vertices.y--;
         
           }
     
           line(t1,t2);
           
    }
    
    void Graphics::fill_top_flat_triangle(Vertex v1, Vertex v2, Vertex v3)
    {
     
         Vertex t1, t2;
    
           t1 =  v1;
           t2 =  v1;
           
           float m1 = (v2.vertices.y-v1.vertices.y)/( v2.vertices.x-v1.vertices.x);
           float m2 = (v3.vertices.y-v1.vertices.y)/( v3.vertices.x-v1.vertices.x);
    
           float z1 = (v2.vertices.y-v1.vertices.y)/( v2.vertices.z-v1.vertices.z);
           float z2 = (v3.vertices.y-v1.vertices.y)/( v3.vertices.z-v1.vertices.z);
     
           float r1 = (v2.vertices.y-v1.vertices.y)/( v2.color.r-v1.color.r);
           float r2 = (v3.vertices.y-v1.vertices.y)/( v3.color.r-v1.color.r);
            
           float g1 = (v2.vertices.y-v1.vertices.y)/( v2.color.g-v1.color.g);
           float g2 = (v3.vertices.y-v1.vertices.y)/( v3.color.g-v1.color.g);
               
           float b1 = (v2.vertices.y-v1.vertices.y)/( v2.color.b-v1.color.b);
           float b2 = (v3.vertices.y-v1.vertices.y)/( v3.color.b-v1.color.b);
        
    /* 
   
         if(m1 == 0) 
           std::cout<<"M1 is zero"<<std::endl;
        if(m2 == 0)
            std::cout<<"M2 is 0"<<std::endl;
           
         if(z1 == 0) 
           std::cout<<"z1 is zero"<<std::endl;
        if(z2 == 0)
            std::cout<<"z2 is 0"<<std::endl;
           
         if(r1 == 0) 
           std::cout<<"r1 is zero"<<std::endl;
        if(r2 == 0)
            std::cout<<"r2 is 0"<<std::endl;
           
         if(g1 == 0) 
           std::cout<<"g1 is zero"<<std::endl;
        if(g2 == 0)
            std::cout<<"g2 is 0"<<std::endl;
        if(b1 == 0) 
           std::cout<<"b1 is zero"<<std::endl;
        if(b2 == 0)
            std::cout<<"b2 is 0"<<std::endl;
            
        int infinte = 100000000; 
         
        if(1/m1 == 0) 
           m1 = infinte;

         if(1/m2 == 0)
           m2 = infinte;
      
        if(1/z1 == 0) 
           z1 = infinte;
       
        if(1/z2 == 0)
           z2 = infinte;
           
         if(1/r1 == 0) 
           r1 = infinte;
        
         if(1/r2 == 0)
           r2 = infinte;
           
         if(1/g1 == 0) 
           g1 = infinte;
        
         if(1/g2 == 0)
           g2 = infinte;
        
         if(1/b1 == 0) 
           b1 = infinte;
        
         if(1/b2 == 0)
           b2 = infinte;

    */ 
              
           while(t1.vertices.y <=v2.vertices.y)
           {
           
                t1.vertices.x  = v1.vertices.x + (t1.vertices.y - v1.vertices.y)/m1;
                t1.vertices.z  = v1.vertices.z + (t1.vertices.y - v1.vertices.y)/z1;
                
                t2.vertices.x  = v1.vertices.x + (t2.vertices.y - v1.vertices.y)/m2;
                t2.vertices.z  = v1.vertices.z + (t2.vertices.y - v1.vertices.y)/z2;
    
                t1.color.r  = v1.color.r + (t1.vertices.y - v1.vertices.y)/r1;
                t2.color.r  = v1.color.r + (t2.vertices.y - v1.vertices.y)/r2;
    
    
                t1.color.g  = v1.color.g + (t1.vertices.y - v1.vertices.y)/g1;
                t2.color.g  = v1.color.g + (t2.vertices.y - v1.vertices.y)/g2;
    
    
                t1.color.b  = v1.color.b + (t1.vertices.y - v1.vertices.y)/b1;
                t2.color.b  = v1.color.b + (t2.vertices.y - v1.vertices.y)/b2;
    
    
                     line(t1,t2);
                
                t1.vertices.y++;
                t2.vertices.y++;
           
           }
          
           line(t1,t2);
     
    }
    
    void Graphics::setpixel(const Vec3& P,Color c)
    {
        int *pixmem32;
        int colour;
    
        int width = screen->w;
        int height = screen->h;
    
        //Check for boundaries
        int x = P.x;
        int y = P.y;
   
        //if (!(x>=0 && x <= width && y >=0 && y<=height)) return;
        if (x<0 || x > width || y < 0 || y > height) return;
    
         if (P.z > Zbuffer[height*x + y])
            return;
        else
            Zbuffer[height*x + y] = P.z;
    
        colour = SDL_MapRGB ( screen->format,c.r,c.g,c.b);
        pixmem32 = (int*) screen->pixels+y*screen->pitch/4+x;
        *pixmem32 = colour;
    
    }
    
    void Graphics::setpixel(int x,int y,float z,  Color c)
    {
        setpixel(Vec3(x,y,z),c);
    }
    
    void Graphics::refresh(){
        SDL_Flip(screen);
    }
    
    void Graphics::clrscr(){
        SDL_Rect R;
        R.x =0; R.y =0;
        R.h = screen->h; R.w = screen->w;
        SDL_FillRect(screen,&R,0);
    
    }
    
    void Graphics::resetZ(){
               delete[] Zbuffer;
              
               Zbuffer = new float[(screen->w)*(screen->h)];
               
               std::fill_n(Zbuffer,(screen->w)*(screen->h),100);
    
    }


    void Graphics::resetLightBuffer(){

               delete[] lightBuffer;
              
               lightBuffer = new float[(screen->w)*(screen->h)];
               
               std::fill_n(lightBuffer,(screen->w)*(screen->h),400);
    }
   
    void Graphics::line(Vertex P1, Vertex P2)
    {
       

        Vertex temp1, temp2;

        if(P1.vertices.x > P2.vertices.x)
        {
                temp1 = P2;
                temp2 = P1;
        }
       
        else
         {
           temp1 = P1;
           temp2 = P2;
         }

       
          
         temp1.vertices.x = round(temp1.vertices.x);
         temp2.vertices.x = round(temp2.vertices.x);

         temp1.vertices.y = round(temp1.vertices.y);
         temp2.vertices.y = round(temp2.vertices.y);

         setpixel(temp1.vertices.x - 1, temp1.vertices.y,temp1.vertices.z, temp1.color);
   
       if(temp1.vertices.x !=temp2.vertices.x)
         {
 
                int slopeZ = (temp2.vertices.z - temp1.vertices.z)/(temp2.vertices.x - temp1.vertices.x);
                
                int slopeR = (temp2.color.r - temp1.color.r)/(temp2.vertices.x - temp1.vertices.x);
                int slopeG = (temp2.color.g - temp1.color.g)/(temp2.vertices.x - temp1.vertices.x);
                int slopeB = (temp2.color.b - temp1.color.b)/(temp2.vertices.x - temp1.vertices.x);

        for(int i = temp1.vertices.x; i <= temp2.vertices.x ;++i)
            {
            
                setpixel(i, temp1.vertices.y,temp1.vertices.z, temp1.color);
              
                temp1.vertices.z += slopeZ; 
                temp1.color.r +=slopeR;             
                temp1.color.g +=slopeG;             
                temp1.color.b +=slopeB;             
            }
         
         } 
       else
        {
        
          setpixel(temp1.vertices.x,temp1.vertices.y,temp1.vertices.z, temp1.color);
       
        }

    }

bool Graphics::WaitQuit()
    {
        SDL_Event event;
        bool keypress = false;
    
        while (!keypress)
        {
            while(SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                //If the cross on the top is pressed it is triggered
                case SDL_QUIT:
                    keypress = true;
                    break;
                //Triggered for keydown
                case SDL_KEYDOWN:
                    keypress = true;
                    break;
                }
            }
        }
        return true; //wait ends
    }
    
    /*---------------------------------------------------------*/
