#include "Matrix.h"
#include <iostream>
#include <vector>
#include <complex>
#include <string>

using namespace std;

bool getRow(string& a, string& row) {
	for (int i = 0; i < a.size() && a[i] != '\\'; ++i);
	row = a.substr(0, i);
	a = a.substr(i);
	return !a.empty();
}

bool getField(string& a, string field) {
	for (int i = 0; i < a.size() && a[i] != ')'; ++i);
	field = a.substr(0, i);
	a = a.substr(i);
	return !a.empty();
}

Matrix<complex<double>> matrixFromString (string a) {
	vector<vector<complex>> temp;
	string row;
	while (getRow(a, row)) {
		string field;
		temp.push_back(vector<complex>{});
		while (getField(row, field)) {
			temp.end()->push_back(complex{real, imaginary});
		}
	}
}

Matrix<complex<double>> stringFromMatrix(const Matrix<complex<double>>& a) {
	
}

int main() {
   Matrix<complex<double>> M1(2,2,1i) ;
   Matrix<complex<double>> M2(4,4,0.0);
   Matrix<complex<double>> H(2,2,1.0/sqrt(2));
   Matrix<complex<double>> M3(3,3,0);
   M3(0,1)=1.0;
   M3(0,2)=1.0;
   M3(2,1)=1.0;
   H(1,1)=H(1,1)*(-1.0);
   for(unsigned int i=0; i<M2.nrows(); i++)
      for(unsigned int j=0; j<M2.ncols(); j++)
         if(i==j)
            M2(i,j)=1.0;
   
   cout << "M1 = " <<M1;
   cout << endl << "M2 = "<<M2 << endl;
   cout << "M1 is type: " <<typeid(M1(0,0)).name() << endl;
   cout << "conjugate of M1 : \n";
   cout << conj(M1);
   cout << endl;
   cout << "M3: \n" << M3 << endl << "M3 transpose: " << endl << trans(M3) << endl;

   
   cout << "Tensor Product M2(x)M1 : ";
   Matrix<complex<double>> M3(tensor(M1,M2));
   cout << M3; main() {
	
	return 0;
}
