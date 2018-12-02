/// ***************************
/// File: Matrix.h 
/// 
/// ***************************
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <complex>
#include <string>

using namespace std;


template <class T>
class Matrix
{
  public:
   Matrix(int = 0, int = 0, T = T(0));// constructor with default parameters
   ~Matrix(); // Destructor
   Matrix(const Matrix&);                 // copy constructor
   
   T& operator() (int, int);     // l-value overloaded operator
   const T& operator() (int, int) const; // r-value overloaded operator
   
   // Vector version of () opertor
   T& operator() (int );     // l-value
   const T& operator() (int) const; // r-value

   Matrix& operator= (const Matrix&); // overloaded assigment operator
   
   Matrix& operator+= (const Matrix&); // binary += operator
   Matrix& operator-= (const Matrix&);
   Matrix& operator*= (const Matrix&);
   Matrix& operator*= (T);     // binary *= for a scalar
   
   void print(ostream&) const;             // print function
   int nrows() const;                      // return object number of rows
   int ncols() const;                      // return object number of cols
   
  protected:
   unsigned int rows; // # of rows
   unsigned int cols; // # Cols 
   T* dPtr;  // Heap ptr
   
   void copy(const Matrix&); // copy Matrix 
};

// ++++++++++++++++++++
// Non-member Functions
// +++++++++++++++++++++
template <class T> Matrix<T> operator- (const Matrix<T>&);                // Negation
template <class T> Matrix<T> operator+ (const Matrix<T>&, const Matrix<T>&); // binary addition  
template <class T> Matrix<T> operator- (const Matrix<T>&, const Matrix<T>&); // binary subtraction
template <class T> Matrix<T> operator* (const Matrix<T>&, const Matrix<T>&); // binary multiplication
template <class T> Matrix<T> operator* (const Matrix<T>&, T);        		// Scaler multiplication RHS
template <class T> Matrix<T> operator* (T d, const Matrix<T>&);      		// Scaler multiplication LHS
template <class T> Matrix<T> tensor(const Matrix<T>&, const Matrix<T>& ); // Tensor Product 
string cDisp(complex<double>, bool);
template <class T> Matrix<T> trans(const Matrix<T>&);   // Transpostion
template <class T> Matrix<T> conj(const Matrix<T>&); // Conjugate of Matrix
template <class T> Matrix<T> dagger(const Matrix<T>&); // Conjugate Transpose (dagger)

template <class T> ostream& operator<< (ostream&, const Matrix<T>&); // overloaded insertion operator

#include "Matrix.cpp"
#endif
   
