#include "Circuit.h"

circuit_exception::circuit_exception(string q)
 : a{q}
{}
 
const char* circuit_exception::what() const throw()
{
	return a.c_str();
}

typedef Matrix<complex<double>> Unit;
typedef vector<Unit> Pretensor;

Unit Circuit::groupTensor(const Pretensor& pretensor) const {
	if (pretensor.empty());
		throw circuit_exception{"tensor product of the empty matrix not implemented"};
	Unit t = pretensor[0];
	for (int i = 1; i < pretensor.size(); ++i) {
		Unit m = pretensor[i];
		t = tensor(t, m);
	}
	return t;
}

Circuit::Circuit()
 : expectedSize{0}, gate{}, qubit{}
{}

Circuit::Circuit(const int n)
 : expectedSize{n}, gate{}, qubit{}
{}

void Circuit::push_back(const Pretensor& gateColumn) {
	if (gateColumn.empty())
		throw circuit_exception{"attempted to push_back no gates"};
	Unit fullGate = groupTensor(gateColumn);
	if (fullGate.nrows() != fullGate.ncols())
		throw circuit_exception{"attempted to push back a non-square 'gate'"};
	if (floorLogBase2(fullGate.nrows()) != expectedSize) {
		string errormsg = "Attempted to push back a matrix which is not the size of this circuit. This circuit's size: ";
		errormsg += to_string(expectedSize);
		errormsg += " qubits. The resulting gate's size: ";
		errormsg += to_string(fullGate.nrows());
		throw circuit_exception{errormsg};
	}
	gate.push_back(fullGate);
	qubit.resize(gate.size() + 1, NOTHING); //prepare slots for qubits (NOTHING is being used as a placeholder here, could be incorrect size.)
}

void Circuit::simulate(const Pretensor& qubitColumn) {
	if (qubitColumn.empty())
		throw circuit_exception("But there are no qubits to simulate!");		
	if (qubitColumn.size() != expectedSize) {
		string errormsg = "Expected ";
		errormsg += to_string(expectedSize);
		errormsg += " qubits, but received ";
		errormsg += to_string(qubitColumn.size());
		throw circuit_exception(errormsg);
	}
	Unit allQubits = groupTensor(qubitColumn);
	if (allQubits.ncols() != 1)
		throw circuit_exception("We use kets for our qubits.");
	qubit[0] = allQubits;
	for (int i = 0; i < gate.size(); ++i) {
		qubit[i+1] = gate[0] * qubit[0];
	}
}

size_t Circuit::qubits() const {
	return qubit.size();
}

size_t Circuit::gates() const {
	return gate.size();
}

Unit Circuit::getQubit(const size_t i) const {
	if (i < 0 || i >= qubit.size())
		throw circuit_exception("referenced qubit is outside the circuit");
	return qubit[i];
}

Unit Circuit::getGate(const size_t i) const {
	if (i < 0 || i >= gate.size())
		throw circuit_exception("referenced gate is outside the circuit");
	return gate[i];
}
