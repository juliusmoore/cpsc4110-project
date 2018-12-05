#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "Matrix.h"
#include "Shared.h"
#include <vector>
#include <exception>

using namespace std;

class Circuit {
	int expectedSize;
	vector<Matrix> gate;
	vector<Matrix> qubit;
public:
	Circuit()
	 : expectedSize{0}, gate{}, qubit{}
	{}
	
	void expand(const int n) {
		if (n < expectedSize)
			throw exception{"The contents of a circuit cannot be destroyed."};
		if (n == expectedSize)
			return;
		for (int i = 0; i < gate.size(); ++i) {
			
		}
	}
};

#endif
