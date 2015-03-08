#ifndef MATRIX_H
#define MATRIX_H

#include<cmath>


    class Matrix
    {
        private:
            float* data;
            int row, col;

        public:
            Matrix(int rows,int column); 
    
            Matrix(const Matrix& mat);
    
            void operator=(const Matrix& mat);
    
            float& operator() (int r, int c);   //mat(i,j)
            float& operator() (int pos) ;       //mat(pos)
    
    
            const float operator() (int r, int c) const;   //mat(i,j)
            const float operator() (int pos) const;       //mat(pos)
    
    
            Matrix operator * (Matrix& mat);    // M = T * M
            Matrix operator + (Matrix& mat);    // C = A + B
            Matrix operator - (Matrix& mat);    // C = A - B
            Matrix operator / (float val);      // C[] = C[] / val
            float dot(Matrix& mat);             // A.dot(B) == (A = A DOT B)
            float magnitude();                  //returns the square root of sum of squares of all element
    
            ~Matrix();
    };




#endif
