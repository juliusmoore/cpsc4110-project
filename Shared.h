#include "Matrix.h"
#include <iostream>
#include <vector>
#include <complex>
#include <string>
#include <cctype>
#include <fstream>
#include <cstdlib>
#include <exception>

#ifndef SHARED_H
#define SHARED_H

extern Matrix<complex<double>> IDENTITY, U2Q_NOT, CNOT, TOFFOLI, U2Q_ONE, HADAMARD, U2Q_IDENTITY, U2Q_ZERO, NOTHING, ONE, ZERO;

//setup globals
void SETUP();

//integer maths
uint64_t floorLogBase2(uint64_t);

//kept from prototyping
long long stringToLongLong(const string& a);
complex<long double> complexFromString(const string& t);
bool getField(string& a, complex<long double>& field);
Matrix<complex<double>> matrixFromStream (istream& a);
Matrix<complex<double>> fileToMatrix(const string& name);

#endif
