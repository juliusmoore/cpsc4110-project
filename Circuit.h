#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "Matrix.h"
#include "Shared.h"
#include <vector>
#include <exception>

using namespace std;

//custom exceptions
class circuit_exception : exception {
	string a;
public:
	circuit_exception(string q = "circuit exception!");
	virtual const char* what() const throw();
};

class Circuit {
	typedef Matrix<complex<double>> Unit;
	typedef vector<Unit> Pretensor;
	int expectedSize;
	vector<Unit> gate;
	vector<Unit> qubit;
private:
	Unit groupTensor(const Pretensor& pretensor) const;
public:
	Circuit();
	
	Circuit(const int n);
	
	void push_back(const Pretensor& gateColumn);
	
	void simulate(const Pretensor& qubitColumn);
	
	size_t qubits() const;
	
	size_t gates() const;
	
	Unit getQubit(const size_t i) const;
	
	Unit getGate(const size_t i) const;
};

#endif
