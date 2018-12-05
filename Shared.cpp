#include "Shared.h"

using namespace std;

Matrix<complex<double>> IDENTITY, U2Q_NOT, CNOT, TOFFOLI, U2Q_ONE, HADAMARD, U2Q_IDENTITY, U2Q_ZERO, NOTHING, ONE, ZERO;

void SETUP() {
	IDENTITY = fileToMatrix("IDENTITY");
	U2Q_NOT = fileToMatrix("U2Q_NOT");
	CNOT = fileToMatrix("CNOT");
	TOFFOLI = fileToMatrix("TOFFOLI");
	U2Q_ONE = fileToMatrix("U2Q_ONE");
	HADAMARD = fileToMatrix("HADAMARD");
	U2Q_IDENTITY = fileToMatrix("U2Q_IDENTITY");
	U2Q_ZERO = fileToMatrix("U2Q_ZERO");
	NOTHING = fileToMatrix("NOTHING");
	ONE = fileToMatrix("ONE");
	ZERO = fileToMatrix("ZERO");
}

uint64_t floorLogBase2(uint64_t a) {
	if (a == 0)
		throw invalid_argument{"The log of zero is undefined."};
	uint64_t i = 0;
	while (a >>= 1) {
		++i;
	}
	return i;
}

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
