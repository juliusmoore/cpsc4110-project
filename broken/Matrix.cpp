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

/// Destructor
template <class T> Matrix<T>::~Matrix(){
   delete [] dPtr;
   dPtr = nullptr;
}

/// ----------------
/// Copy Constructor
/// ----------------
template <class T> Matrix<T>::Matrix(const Matrix& m){ copy(m); }

/// ---------------------------------------
/// Array element operator
/// l-value version 
///
template <class T> T& Matrix<T>::operator()(int r, int c)
{
   assert(r >= 0 && r < rows && c >= 0 && c < cols);
   return dPtr[r * cols + c];
}

/// r-value version

template <class T> const T& Matrix<T>::operator()(int r, int c) const
{
   assert(r >= 0 && r < rows && c >= 0 && c < cols); // Assert in-bounds
   return dPtr[r * cols + c];
}
/// ----------------------------
 
/// ---------------
/// Array element operator - single argument if matrix is a row or column vector
///
/// l-value version 
template <class T> T& Matrix<T>::operator()(int v)
{
   assert(rows == 1 || cols==1); // Assert Matrix is either a row or column vector
   return dPtr[v];
}  
/// r-value version
template <class T> const T& Matrix<T>::operator()(int v) const
{
   assert(rows == 1 || cols==1); // Assert Matrix is either a row or column vector
   return dPtr[v];
}
/// ----------------------------

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
	         oStr <<setw(8) << cDisp((*this)(i,j), true) << setw(2) << ( ((j+1)<cols) ? " ," : " " );
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
/// -------------------------
/// Transposition
/// -------------------------
template <class T> Matrix<T> trans(const Matrix<T>& m)
{
   unsigned int r=m.nrows();
   unsigned int c=m.ncols();
   Matrix<T> tmp(c,r,0);
   
   for(unsigned int i=0; i< c; i++)
      for(unsigned int j=0; j < r; j++)
         tmp(i,j)=m(j,i);
   return tmp;
}

template <class T> Matrix<T> conj(Matrix<T>& m)
{
   Matrix<T> tmp(m);

      unsigned int nCols=m.ncols();
      unsigned int nRows=m.nrows();
      for(unsigned int i=0; i < nRows; i++)
         for(unsigned int j=0; j < nCols; j++)
            tmp(i,j)=std::conj(m(i,j));
      
   return tmp;
}

/// ------------------------------
/// Dagger (conjugate transpose)
/// ------------------------------
template <class T> Matrix<T> dagger(const Matrix<T>& m)
{
   unsigned int r=m.nrows();
   unsigned int c=m.ncols();
   Matrix<T> tmp(c,r,0);
   
   for(unsigned int i=0; i< c; i++)
      for(unsigned int j=0; j < r; j++)
         tmp(i,j)=std::conj(m(j,i));
   return tmp;
}

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

/// ---------------------------------------------------------------------
/// cDisp() - Prints a simplified and more readible complex number
///
/// Details: Takes a complex number as an agument and returns a string of
///          the number in the form a+bi. If either the real or imaginary
///          imaginary part of the number are zero they are ommitted. If the
///          imaginary coeffient is -+1 it is omitted and only +-i is added.
/// --------------------------------------------------------
string cDisp(complex<double> c, bool nobrack_override=false){
	const double IOTA_CONST=0.00000000000001; // Constant very small (almost zero) to allow for the fact that
                                             // due to inexact representations of irrational numbers something 
                                             // that should be zero will not be recognized as zero in equality
                                             // comparisons.
	std::ostringstream strs;
	std::string str;
   
	bool i_gt_zero=true; // imaginary part of complex number greater than zero. 
                        // Used to determine what arithmetic operator to display (- or +)

	bool i_true=true; // Set to false if imaginary part of complex number is 0.
                     // If set to false the imaginary part is not displayed

	bool i_one=false; // set to true if imaginary part of complex number is +-1. 
                     // If true only i is displayed  instead of 1i

	bool r_true=true; // real part of complex number. If real part is 0 set to false.

	bool brackets_bool=false; // whether to display brackets around the number
                             // If there is both a non-zero real and imaginary part
                             // this is set to true and  brackets are added.



///--- Determine Characteristics of the complex number -----
///--- Complex number: a+bi  where: 
///                           a: real coefficient  
///                           b: imaginary coefficient
   // Check to see if b=0
   // ( in the range of [-IOTA_CONST, +IOTA_CONT] )
   if((imag(c) < IOTA_CONST )&&(imag(c) > -IOTA_CONST ))
		 i_true=false;		 
   else{ // else b!=0
   // Check to see if b=+-1 by checking if its absolute value is in the range: [1-IOTA_CONST, 1+IOTA_CONST] 
	   if((abs(imag(c)) < (1. + IOTA_CONST)) && (abs(imag(c)) > (1. - IOTA_CONST)))
		   i_one=true;
		// Check to see if b<0 (ie negative)
	   if(imag(c) < -IOTA_CONST)
		   i_gt_zero=false;
   } // End of Imaginary analysis

 // Check to see if a == 0
	if((real(c) < IOTA_CONST) && (real(c) > -IOTA_CONST))
		r_true=false;

/// ------ Build statment to return based on the chracteristics  -----------
// ** CASE: a != 0 and b != 0:
   if(i_true && r_true){
		if(!nobrack_override){ // If nobrack_override set to true don't print brackets even though both a,b != 0
         brackets_bool=true; 	// Set to true so closing bracket is added 
		   strs << "(";
      }
      strs <<real(c) << (i_gt_zero ? "+" : "-"); //ternary statement to put +,- if bi is either +,-
	
   // * SUB-CASE: b != 1  (print coeffient):
		if(!i_one) 		///  if b in a+bi is not equal to 1 add b
			strs << abs(imag(c)); 
		strs<<"i"; // Add i to the end
	} 
// ** CASE: a != 0, b == 0:
   else if(r_true)		/// Only Real value in complex number
      strs <<real(c);

// ** CASE: a == 0, b != 0 
	else if(i_true){	 
   // * SUB-CASE: b != +-1 (add coefficent followed by "i"):
		if(!i_one)			
			strs << imag(c) << "i"; // Add coeffient followed by "i"
   // * SUB-CASE: b == +-1  (skip coeffient and only add "+i" or "-i"):
      else 
		   strs << (i_gt_zero ? "i" : "-i");		/// If imaginary coeffient is -1 print -i
	}
// ** CASE: a==0 b==0 :
   else
      strs << 0;

	if(brackets_bool) // Close bracket if opened
		strs << ")"; 

	str = strs.str(); // Convert to a string
	return str; // Return string
}