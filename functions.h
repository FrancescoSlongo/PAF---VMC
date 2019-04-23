#ifndef VMC_H
#define VMC_H

// Zona librerie
#include <iostream>				// For input and output.
#include <fstream>				// For printing the results in txt format.
#include <iomanip>				// For modifying the output in the txt.
#include <cmath>				// For mathematical functions.
#include <string>				// For modify string easily.
#include <random>				// For random number generator.

// Funzione per calcolare la wavefunction dato l'array in ingresso
double Wavefunction(double* R, double omega, double alpha, double beta, int wftype);

// Funzione per calcolare l'energia
double Localenergy(double* R, double omega, double alpha, double beta, int wftype);

#endif // VMC_H
