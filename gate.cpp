#include "Matrix.h"
#include <iostream>
#include <vector>
#include <complex>
#include <string>
#include <cctype>
#include <fstream>
#include <cstdlib>

using namespace std;

long long stringToLongLong(const string& a) {
	if (a.empty())
		return 0;
	long long result = 0;
	for (int i = 0; i < a.size(); ++i) {
		if (isdigit(a[i])) {
			result *= 10;
			result += a[i] - 48;
		}
	}
	if (a[0] == '-')
		return -result;
	else
		return result;
}

complex<long double> complexFromString(const string& t) {
	int mode = 0;
	string e[4];
	bool negable = true;
	for (int i = 0; i < t.size(); ++i) {
		const char& a = t[i];
		switch (a) {
			case '-':
				if (!negable)
					continue;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				negable = false;
				e[mode].push_back(a);
				continue;
			case '.':
				if (mode == 0 || mode == 2) {
					++mode;
					negable = false;
				}
				continue;
			case ',':
				if (mode == 1 || mode == 0) {
					mode = 2;
					negable = true;
				}
				continue;
			default:
				continue;
		}
	}
	long double d[4];
	for (int i = 0; i < 4; ++i) {
		//cout << "e[" << i << "] = " << e[i] << endl;
		if (e[i] == "")
			d[i] = 0;
		else
			d[i] = stringToLongLong(e[i]);
	}
	if (!e[0].empty() && e[0][0] == '-')
		d[1] *= -1.0l;
	if (!e[2].empty() && e[2][0] == '-')
		d[3] *= -1.0l;
	long double real, imaginary;
	if (d[1] != 0)
		real = d[0] + d[1] / pow(10.0l, static_cast<long double>(e[1].size()));
	else
		real = d[0];
	if (d[3] != 0)
		imaginary = d[2] + d[3] / pow(10.0l, static_cast<long double>(e[3].size()));
	else
		imaginary = d[2];
	return complex<long double>{real, imaginary};
}

bool getField(string& a, complex<long double>& field) {
	int i, j;
	for (i = 0; i < a.size() && isspace(a[i]); ++i);
	a = a.substr(i);
	if (a == "")
		return false;
	for (i = 0; i < a.size() && !isspace(a[i]); ++i);
	for (j = i; j < a.size() && isspace(a[j]) == ' '; ++j);
	field = complexFromString(a.substr(0, i));
	a = a.substr(j);
	return true;
}

Matrix<complex<double>> matrixFromStream (istream& a) {
	vector<vector<complex<long double>>> result;
	string row, field;
	while (getline(a, row)) {
		if (row.empty())
			break;
		//cout << "About to start another row" << endl;
		result.push_back(vector<complex<long double>>{});
		complex<long double> field;
		while (getField(row, field)) {
			//cout << "About to push back a complex number" << endl;
			result[result.size()-1].push_back(field);
			//cout << "Pushed back a complex number" << endl;
		}
		//cout << "Row Complete" << endl;
	}
	//few lines that end this function assume a matrix
	//cout << "About to transfer values" << endl;
	Matrix<complex<double>> m{result.size(), result[0].size()};
	for (int i = 0; i < result.size(); ++i) {
		for (int j = 0; j < result[i].size(); ++j) {
			m(i,j) = result[i][j];
		}
	}
	//cout << "About to return a matrix" << endl;
	return m;
}

Matrix<complex<double>> fileToMatrix(const string& name) {
	ifstream in;
	in.open(name);
	return matrixFromStream(in);
}

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
