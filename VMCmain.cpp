// Codice contenente il main del progetto
// Zona librerie
#include <iostream>				// For input and output.
#include <fstream>				// For printing the results in txt format.
#include <iomanip>				// For modifying the output in the txt.
#include <cmath>				// For mathematical functions.
#include <string>				// For modify string easily.
#include <random>				// For random number generator.

#include "functions.h"			// Nostra libreria con funzioni

using namespace std;  // In C++ si lavora in ambienti, chiamando all'inizio si evita il problema ed è come in C

int main() {
	// Chiamo il tutto il necessario per il generatore di numeri casuali
	random_device rd;
	mt19937_64 gen(rd());
	uniform_real_distribution<double> RNG(0, 1);

	// Inizializzo le variabili che mi servono
	int MCC = 1000;  // Numero di MonteCarlo cycles
	double alpha = 1; // Paramentro funzione d'onda
	double E = 0, sumE = 0, sumE2 = 0; // Valore dove salvare le variabile E e E^2
	double rstep = 0; // Incremento nel VMC
	double omega = 1; // Frequenza dell'oscillatore armonico
	double accratio = 0; // Ratio di accettazione del metropolis
	int ncut = 0; // Valore a cui incominciare a prendere le misure
	// Posizione elettroni
	double* Rold = new double[6]; // Inizializzazione con memoria dinamica, viene usato come un array normale
	double* Rnew = new double[6];
	// Inizializzo a caso le posizioni
	for (int i = 0; i < 6; i++) {
		Rold[i] = RNG(gen) - 0.5;
		Rnew[i] = Rold[i];
	}
	// Funzioni d'onda calcolanata nel punto
	double Psiold = 0, Psinew = 0;

	for (int i = 0; i < 5; i++) { // Ciclo su diversi valori di alpha
		// Definisco rstep in funzione di alpha
		rstep = 2.5/sqrt(alpha*omega);
		// Calcolo la wavefunction nel punto
		Psiold = Wavefunction(Rold, omega, alpha);
		for (int j = 0; j < MCC; j++) { // Ciclo sui MCC
			// Nuovo valore posizioni
			for (int i = 0; i < 6; i++) {
				Rnew[i] = Rold[i] + rstep*(RNG(gen) - 0.5);
			}
			// Calcolo la wavefunction nel punto
			Psinew = Wavefunction(Rnew, omega, alpha);
			// Metropolis
			if (RNG(gen) <= Psinew * Psinew / (Psiold*Psiold)) {  // Accetto la mossa
				for (int i = 0; i < 6; i++) { 
					Rold[i] = Rnew[i];
				}
				Psiold = Psinew;
				accratio += 1;
			}
			else { // Rifiuto la mossa
				for (int i = 0; i < 6; i++) {
					Rnew[i] = Rold[i];
				}
			}
			if (j > ncut) {
				E = Localenergy(Rnew, omega, alpha);
				sumE += E;
				sumE2 += E * E;
			}

		}
		// Medio i risultati
		sumE = sumE / (MCC - ncut); // Medio i valori
		sumE2 = sumE2 / (MCC - ncut);
		accratio = accratio / (MCC - ncut);
		// Print a schermo dei risultati
		cout << "Alpha " << alpha << " Media " << sumE << " Varianza " << sumE2 << " Percentuale di accettazione " << accratio*100 << "%" << endl; // Print a terminale
		// Resetto i valori per un nuovo alpha
		sumE = 0;
		sumE2 = 0;
		accratio = 0;
		alpha += 1;
	}

	system("pause"); // Comando che non fa chiudere in automatico la finestra di output in Visual Studio
	return 0;
}