#include "functions.h"

using namespace  std;

double Wavefunction(double* R, double omega, double alpha) {
	// Definisco due raggi per comodità
	double r1 = 0, r2 = 0; 
	for (int i = 0; i < 3; i++) {
		r1 = R[i] * R[i];
		r2 = R[i + 3] * R[i + 3];
	}

	return exp(-alpha * omega*(r1 + r2) / 2); // Nota che r1 e r2 sono già al quadrato
}

double Localenergy(double* R, double omega, double alpha) {
	// Definisco due raggi per comodità
	double r1 = 0, r2 = 0;
	for (int i = 0; i < 3; i++) {
		r1 = R[i] * R[i];
		r2 = R[i + 3] * R[i + 3];
	}

	return 0.5*pow(omega, 2)*(r1 + r2)*(1 - pow(alpha, 2)) + 3 * alpha*omega;   // Nota che r1 e r2 sono già al quadrato
}