#include <iostream>
#include <vector>
#include <complex>
#include <string>
#include <cctype>
#include <fstream>
#include <cstdlib>

#include "Matrix.h"
#include "Shared.h"
#include "Circuit.h"

using namespace std;

int main() {
	SETUP();
	try {
		Circuit c{1};
		vector<Matrix<complex<double>>> t;
		cout << "About to add gates" << endl;
		t.push_back(HADAMARD);
		c.push_back(t);
		cout << "About to add qubits" << endl;
		t.clear();
		t.push_back(ONE);
		c.simulate(t);
		cout << "\n\n";
		cout << "We have output ready!" << endl;
		cout << "Valid Circuit? " << c.isValid() << endl;
		cout << "The circuit is also a Matrix!" << endl;
		cout << c.asMatrix();
		cout <<  endl << endl;
		cout << "Gates: " << endl;
		for (int i = 0; i < c.gates(); ++i) {
			cout << c.getGate(i) << endl;
		}
		cout << "Qubits: " << endl;
		for (int i = 0; i < c.qubits(); ++i) {
			cout << c.getQubit(i) << endl;
		}
	} catch (circuit_exception e) {
		cout << e.what() << endl;
	}
	return 0;
}

/*
int main() {
	cout << "...I..." << endl;
	string t;
	while (true) {
		cout << endl;
		system("ls");
		cout << "Name a matrix: " << flush;
		cin >> t;
		Matrix<complex<double>> m = fileToMatrix(t);
		cout << endl;
		cout << t << ":\n";
		cout << m << endl;
	}
	return 0;
}
*/

/*
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
*/
