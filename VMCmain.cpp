// Codice contenente il main del progetto
// Zona librerie
#include <iostream>				// For input and output.
#include <fstream>				// For printing the results in txt format.
#include <iomanip>				// For modifying the output in the txt.
#include <cmath>				// For mathematical functions.
#include <string>				// For modify string easily.
#include <random>				// For random number generator.

#include "functions.h"			// Nostra libreria con funzioni

using namespace std;  // In C++ si lavora in ambienti, chiamando all'inizio si evita il problema ed � come in C
ofstream ofile; // Ambiente print in txt
int main() {
	// Chiamo il tutto il necessario per il generatore di numeri casuali
	random_device rd;
	mt19937_64 gen(rd());
	uniform_real_distribution<double> RNG(0, 1);

	// tipo di wavefunction e hamiltoniana:
	int wftype = 0; 
	// 0 -> wavefunction gaussiana con solo alpha e senza interazione culombiana
	// 1 -> wavefunction gaussiana con solo alpha e con interazione culombiana
	// 2 -> wavefunction con due parametri e interazione culombiana

	// Nome file
	string outname = "VMC_";
	outname.append(to_string(wftype));
	outname.append(".txt");

	// inizializzo variabili per la fisica della simulazione
	double alpha = 1; // Paramentro funzione d'onda: sigma gaussiana
	double beta = 0.15; // Parametro funzione d'onda: Jastrow term
	double omega[4] = { 0.01, 0.5, 1, 5}; // Frequenza dell'oscillatore armonico
	double n_beta = 10; // Numero di beta visitati nel ciclo
	double n_alpha = 5; // Numero di alpha visitati nel ciclo
	double step_beta = 0.01; // incremento di beta
	double step_alpha = 1; // incremento di alpha

	// Inizializzo le variabili per la simulazione
	int MCC = 100000;  // Numero di MonteCarlo cycles
	double E = 0, sumE = 0, sumE2 = 0; // Valore dove salvare le variabile E e E^2
	double error = 0; // valore dove salvare l'errore sull'energia
	double Emin = 10, errore_Emin = 0; // valore dove salvare l'energia minima
	double betamin = 0, alphamin = 0; // valori dove salvare alpha e beta che minimizzano l'energia 
	double rstep = 0; // Incremento nel VMC
	double accratio = 0; // Ratio di accettazione del metropolis
	int ncut = 10; // Valore a cui incominciare a prendere le misure
	
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

	ofile.open(outname);
	// Ciclo su diversi valori di omega
	for (int q = 0; q < 4; q++) {
		// Ciclo su diversi valori di beta
		for (int p = 0; p < n_beta; p++) {
			cout << "Omega " << omega[q] << " Beta " << beta << endl;
			ofile << "Omega " << omega[q] << " Beta " << beta << endl;
			// Ciclo su diversi valori di alpha
			for (int s = 0; s < n_alpha; s++) {

				// Definisco rstep in funzione di alpha
				rstep = 1.375 / sqrt(alpha * omega[q]);
				// Calcolo la wavefunction nel punto
				Psiold = Wavefunction(Rold, omega[q], alpha, beta, wftype);
				for (int j = 0; j < MCC; j++) { // Ciclo sui MCC
					// Nuovo valore posizioni
					for (int i = 0; i < 6; i++) {
						Rnew[i] = Rold[i] + rstep * (RNG(gen) - 0.5);
					}
					// Calcolo la wavefunction nel punto
					Psinew = Wavefunction(Rnew, omega[q], alpha, beta, wftype);

					// Metropolis
					if (RNG(gen) <= Psinew * Psinew / (Psiold * Psiold)) {  // Accetto la mossa
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
						E = Localenergy(Rnew, omega[q], alpha, beta, wftype);
						sumE += E;
						sumE2 += E * E;
					}

				}
				// Medio i risultati
				sumE = sumE / (MCC - ncut); // Medio i valori
				sumE2 = sumE2 / (MCC - ncut);
				error = sqrt(sumE2 - sumE * sumE);
				accratio = accratio / (MCC - ncut);
				// Print a schermo dei risultati
				cout << "Alpha " << alpha << " Media " << sumE << " Errore (1 sigma) " << error << " Percentuale di accettazione " << accratio * 100 << "%" << endl;
				// Print a schermo dei risultati
				ofile << "Alpha " << alpha << " Beta " << beta << " Media " << sumE << " Errore (1 sigma) " << error << " Percentuale di accettazione " << accratio * 100 << "%" << endl;
				// Trovo l'energia minima
				if (sumE < Emin) {
					Emin = sumE;
					errore_Emin = error;
					betamin = beta;
					alphamin = alpha;
				}
				// Resetto i valori per un nuovo alpha
				sumE = 0;
				sumE2 = 0;
				accratio = 0;
				alpha += step_alpha;
			}
			// resetto il valore di beta
			beta += step_beta;
			alpha = alpha - n_alpha * step_alpha;

			// Se non mi serve beta esco dal ciclo su beta
			if (wftype != 2) {
				p = n_beta;
			}
		}
		cout << "Energia minima " << Emin << " errore (1 sigma) " << errore_Emin << " beta " << betamin << " alpha " << alphamin << endl;
	}
	ofile.close();
	system("pause"); // Comando che non fa chiudere in automatico la finestra di output in Visual Studio
	
	return 0;
}
