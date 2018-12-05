#include "Matrix.h"
#include <iostream>
#include <vector>
#include <complex>
#include <string>
#include <cctype>
#include <fstream>
#include <cstdlib>

#ifndef SHARED_H
#define SHARED_H

extern Matrix<complex<double>> IDENTITY, U2Q_NOT, CNOT, TOFFOLI, U2Q_ONE, HADAMARD, U2Q_IDENTITY, U2Q_ZERO;

void SETUP();
long long stringToLongLong(const string& a);
complex<long double> complexFromString(const string& t);
bool getField(string& a, complex<long double>& field);
Matrix<complex<double>> matrixFromStream (istream& a);
Matrix<complex<double>> fileToMatrix(const string& name);

#endif
