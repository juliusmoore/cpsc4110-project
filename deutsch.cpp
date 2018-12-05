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
		cout << "Welcome to the Deutsch!" << endl;
		cout << "0 : f(x) = 0" << endl;
		cout << "1 : f(x) = 1" << endl;
		cout << "2 : f(x) = x" << endl;
		cout << "3 : f(x) = NOT(x)" << endl;
		cout << endl;
		cout << "Enter an option about and observed the results: " << flush;
		string line;
		getline(cin, line);
		if (line.empty()) {
			cout << "I do not understand." << endl;
			return 0;
		}
		Circuit c{2};
		Matrix<complex<double>> uf;
		switch (line[0] - 48) {
			case 0:
				uf = U2Q_ZERO;
				break;
			case 1:
				uf = U2Q_ONE;
				break;
			case 2:
				uf = U2Q_IDENTITY;
				break;
			case 3:
				uf = U2Q_NOT;
				break;
			default:
				cout << "I do not understand" << endl;
				return 0;
		}
		vector<Matrix<complex<double>>> t;
		t.push_back(HADAMARD);
		t.push_back(HADAMARD);
		c.push_back(t);
		t.clear();
		t.push_back(uf);
		c.push_back(t);
		t.clear();
		t.push_back(HADAMARD);
		t.push_back(IDENTITY);
		c.push_back(t);
		t.clear();
		t.push_back(ZERO);
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
		cout << "Qubits: " << c.qubits() << endl;
		for (int i = 0; i < c.qubits(); ++i) {
			cout << c.getQubit(i) << endl;
		}
		cout << "Let's recap that final line: " << endl;
		cout << c.getOutput() << endl;
	} catch (circuit_exception e) {
		cout << e.what() << endl;
	}
	return 0;
}
