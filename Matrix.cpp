/// --------------------------------
/// File: Matrix.cpp 
/// 
/// --------------------------------
#include <iostream>
#include <iomanip>
#include <cassert>
#include <complex>
#include "Matrix.h"

using namespace std;

/// ------------------
/// Constructor
template <class T> Matrix<T>::Matrix(int r, int c, T initVal){
   if(r > 0 && c > 0){
      rows = r;
      cols = c;
      dPtr = new T[rows*cols];
      for(unsigned int i=0; i<rows*cols; i++) // Set values
		dPtr[i] = initVal;  
   }
   else
   {
      rows = cols = 0;
   }
}

/// ----------
/// Destructor
template <class T> Matrix<T>::~Matrix(){
   delete [] dPtr;
   dPtr = nullptr;
}

/// ----------------
/// Copy Constructor
/// ----------------
template <class T> Matrix<T>::Matrix(const Matrix& m){ copy(m); }

/// ---------------
/// Array element operator
/// l-value version 
/// ---------------
template <class T> T& Matrix<T>::operator()(int r, int c)
{
   assert(r >= 0 && r < rows && c >= 0 && c < cols);
   return dPtr[r * cols + c];
}
   
/// ---------------
/// Array element operator
/// r-value version
/// ---------------
template <class T> const T& Matrix<T>::operator()(int r, int c) const
{
   assert(r >= 0 && r < rows && c >= 0 && c < cols); // Assert in-bounds
   return dPtr[r * cols + c];
}
   
/// ---------------
/// assigment operator
/// ---------------
template <class T> Matrix<T>& Matrix<T>::operator=(const Matrix& m)
{
   if(this != &m) // Check not doing self assignment
   {
      if(rows*cols > 0){
		delete [] dPtr;
		dPtr = nullptr;
      }
      copy(m);
   }
   return *this; 
}
// ---------------
// copy function
// ---------------
template <class T> void Matrix<T>::copy(const Matrix& m)
{
   rows = m.rows;
   cols = m.cols;
   dPtr = new T[rows*cols];
   for(unsigned int i=0; i<rows*cols; i++)
      dPtr[i] = m.dPtr[i];
}
      
/// ---------------
/// [ += ] Matrix Addition
/// ---------------
template <class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix& m)
{
   assert(nrows() == m.nrows() && ncols() == m.ncols());
   for(unsigned int i=0; i<m.rows*m.cols; i++)
      dPtr[i] = dPtr[i] + m.dPtr[i]; // add corresponding elements
   return *this;
}

/// ---------------
/// [ -= ] Matrix Subtractoin 
/// ---------------
template <class T> Matrix<T>& Matrix<T>::operator-=(const Matrix& m)
{
   assert(nrows() == m.nrows() && ncols() == m.ncols());
   for(unsigned int i=0; i< rows * cols; i++)
      dPtr[i] = dPtr[i] - m.dPtr[i];
   return *this;
}

/// ---------------
///  [ *= ] Matrix  Multiplication 
/// ---------------
template <class T> Matrix<T>& Matrix<T>::operator*=(const Matrix& m)
{
   assert(cols == m.rows); // check for matching dimension
   Matrix tmp(rows, m.cols);
   for(unsigned int i = 0; i < rows; i++)
      for(unsigned int j = 0; j < m.cols; j++)
	 for(unsigned int k = 0; k < cols; k++)
	    tmp(i,j) += (*this)(i,k) * m(k,j); // calls overloaded ()
   *this = tmp;
   return *this; // allows for concatenation of *=
}

/// ---------------
/// [ *= ] Scaler Multiplication
/// ---------------
template <class T>
Matrix<T>& Matrix<T>::operator*=(T d)
{
   for(unsigned int i=0; i<rows; i++)
      for(unsigned int j = 0; j < cols; j++)
	 (*this)(i,j) *= d; // multiply each matrix element by d
   // or
   // for(unsigned int i=0; i<rows*cols; i++)
   //    dPtr[i] *= d;
   return *this;
}

/// -----------------------------------
/// Print Contents of Matrix
/// ----------------------------------
template <class T> void Matrix<T>::print(ostream& oStr) const
{
   if(rows > 0 && cols > 0)
      for(unsigned int i=0; i<rows; i++)
      {
	 oStr << '|';
	 for(int j=0; j<cols; j++)
	    oStr << setw(8) << (*this)(i,j);
	 oStr << " |" << endl;
      }
   else
      cout << "[]" << endl; /// Empty
}

/// ------------------------------------------------------------
/// Functions to return the number of rows and columns of matrix
template <class T> int Matrix<T>::nrows() const{ return rows;}
template <class T>int Matrix<T>::ncols() const { return cols;}
/// -----------------------------------------------------------

/// +++++++++++++++++++++++++++++++++++++ 
///         Non-Member Functions
/// ++++++++++++++++++++++++++++++++++++++

/// -------------------------
/// Matrix Matrix Addition
/// --------------------------
template <class T> Matrix<T> operator+(const Matrix<T>& m1, const Matrix<T>& m2){
   assert(m1.nrows() == m2.nrows() && m1.ncols() == m2.ncols()); // assert rows and columns match
   Matrix<T> tmp= m1; // copy first to new matrix
   tmp+= m2;         // add second matrix to it
   return tmp;       // return new summed matrix
}

/// ----------------------------
/// Subtraction (is negation combined with addition)
/// ----------------------------
template <class T>Matrix<T> operator-(const Matrix<T>& m1, const Matrix<T>& m2){ return m1 + (-m2); }


template <class T> Matrix<T> operator+(const Matrix<T>& m){ return m; } // simply return matrix if unary +

/// ---------
/// Negation
/// ---------
template <class T> Matrix<T> operator-(const Matrix<T>& m){ return m * -1.0; }


/// Non-member Matrix Matrix multiplicatoin
template <class T> Matrix<T> operator*(const Matrix<T>& m1, const Matrix<T>& m2)
{
   Matrix<T> tmp(m1); // Copy m1 to tmp
   tmp*= m2; // Multiply 
   return tmp; 
}

/// ------------------------------
/// Scaler Multiplication from LHS
/// -----------------------------
template <class T> Matrix<T> operator* (T d, const Matrix<T>& m)
{
   Matrix<T> tmp(m);
   tmp*= d;
   return tmp;
}

/// --------------------------------
/// Tensor Product of two Matrices
/// --------------------------------
template <class T> Matrix<T> tensor(Matrix<T>& a, Matrix<T>& b)
{  
   int aRows = a.nrows();
   int aCols = a.ncols();
   int bRows = b.nrows();
   int bCols = b.ncols();

	Matrix<T> tmp(aRows*bRows,aCols*bCols);
	for(int i=0; i<aRows; i++)
		for(int j=0; j<aCols; j++)
			for(int ii=0; ii < bRows; ii++)
				for(int jj=0; jj<bCols; jj++)
					tmp(i*bRows+ii,j*bCols+jj)=a(i,j)*b(ii,jj);
			
	return tmp;
	
}

template <class T> Matrix<T> trans(Matrix<T>& m)
{
   Matrix<T> tmp(m);
   unsigned int r=m.nrows();
   unsigned int c=m.ncols();
   for(unsigned int i=0; i< r; i++)
      for(unsigned int j=0; j < c; j++)
         tmp(i,j)=m(j,i);
   return tmp;
}

template <class T> Matrix<T> conj(Matrix<T>& m)
{
   Matrix<T> tmp(m);
   if(typeid(m(0,0)).name()=="St7complexIdE")
   {
      unsigned int nCols=m.ncols();
      unsigned int nRows=m.nrows();
      for(unsigned int i=0; i < nRows; i++)
         for(unsigned int j=0; j < nCols; j++)
            tmp(i,j)=std::conj(m(i,j));
      
   }
   return tmp;
}

/// ------------------------------
/// Scaler Multiplication from RHS
/// -----------------------------
template <class T> Matrix<T> operator*(const Matrix<T>& m, T d){ return d * m; }

/// ---------------
/// ostream insertion
/// ---------------
template <class T> ostream& operator<<(ostream& oStr, const Matrix<T>& m)
{
   m.print(oStr); // calls member function print.
   return oStr;   // this allows for cascading of << operator
}



