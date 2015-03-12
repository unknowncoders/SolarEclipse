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
    
    void Graphics::setpixel(int x,int y,float z,  Color c){
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
    
    void Graphics::line(const Vertex& P1,const Vertex& P2){
    
            float xstart = P1.vertices.x;
            float xend = P2.vertices.x;
            float ystart = P1.vertices.y;
            float yend = P2.vertices.y;
    
            float z1 = P1.vertices.z;
            float z2 = P2.vertices.z;
    
            Color c1 = P1.color;
            Color c2 = P2.color;
    
            float dx = abs(xend - xstart);
            float dy = abs(yend - ystart);
    
            float xinc = (xend>xstart ? 1 : -1);
            float yinc = (yend>ystart ? 1 : -1);	
    
            float twodx = 2*dx;
            float twody = 2*dy;
            float twodydx = twody - twodx;
    
            float x = xstart;
            float y = ystart;	
    
            float z;
            Color c;
    
    
        setpixel(round(x),round(y),z1, c1);
    	
    	if(dx > dy)
    	{
    		float p = twody - dx;
    		
    		while(round(x) != round(xend))
    		{
                z = z1 +((z2-z1)*(x-xstart))/(xend-xstart);
                c.r = c1.r +((c2.r-c1.r)*(x-xstart))/(xend-xstart);
                c.g = c1.g +((c2.g-c1.g)*(x-xstart))/(xend-xstart);
                c.b = c1.b +((c2.b-c1.b)*(x-xstart))/(xend-xstart);
                  
                x += xinc;
                
    
    			if(p<0)
    			{
    				p += twody;	
    			}
    			else
    			{	
    				y += yinc;
    				p += twodydx;
    			}
                 setpixel(round(x),round(y),z, c);
    		}
    	}
    	
    	else
    	{
    		float p = twodx - dy;
    		
    		while(round(y) != round(yend))
    		{
    
                z = z1 +((z2-z1)*(y-ystart))/(yend-ystart);
           
                c.r = c1.r +((c2.r-c1.r)*(y-ystart))/(yend-ystart);
                c.g = c1.g +((c2.g-c1.g)*(y-ystart))/(yend-ystart);
                c.b = c1.b +((c2.b-c1.b)*(y-ystart))/(yend-ystart);
                
                y += yinc;
    			
                if(p <0)
    			{
                        p += twodx;
                }
    		
                else
    			{
    				x += xinc;
    				p -= twodydx;
    			}
                 
                setpixel(round(x),round(y),z, c);
    		}
    
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
