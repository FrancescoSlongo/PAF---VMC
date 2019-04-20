#include "functions.h"

using namespace  std;

double Wavefunction(double* R, double omega, double alpha, double beta, int wftype) {
	// Definisco due raggi e distanza tra elettroni per comodit�
	double r1 = 0, r2 = 0; 
	// Inizializzo il valore dell'output
	double wfvalue = 0;

	for (int i = 0; i < 3; i++) {
		r1 = r1 + R[i] * R[i];
		r2 = r2 + R[i + 3] * R[i + 3];

		r12 = r12 + pow(R[i]-R[i+3], 2); // distanza tra elettroni
	}

	r12 = sqrt(r12); // prendo la radice dei quadrati
	
	// calcolo wavefunction in modo diverso in base al tipo di funzione che voglio
	// 0 -> wavefunction gaussiana con solo alpha e senza interazione culombiana
	// 1 -> wavefunction gaussiana con solo alpha e con interazione culombiana
	// 2 -> wavefunction con due parametri e interazione culombiana

	wfvalue = exp(-alpha * omega*(r1 + r2) / 2); // parte gaussiana dell wf

	if (wftype == 0 || wftype = 1) {
		return wfvalue; // va bene se unico parametro è alpha
	}

	wfvalue = wfvalue* exp(0.5*r12/(1+beta*r12)); // Jastrow term, correlazione tra posizione dei due elettroni

	if (wftype == 2) {
		return wfvalue; // va bene quando ho entrambi i parametri
	}

	// non ritorno niente se non setto il valore di wftype 
	// in questo modo ci accorgiamo dell'errore

	// Nota che r1 e r2 sono gi� al quadrato. Zeno: nel ciclo non erano sommate tutte e tre le componenti
}

double Localenergy(double* R, double omega, double alpha, double beta, int wftype) {
	// Definisco due raggi al quadrato e distanza tra due elettroni per comodit�
	double r1 = 0, r2 = 0, r12 = 0;
	// Inizializzo valore di energia locale (output)
	double Eloc = 0;

	for (int i = 0; i < 3; i++) {
		r1 = r1 + R[i] * R[i]; 
		r2 = r2 + R[i + 3] * R[i + 3];

		r12 = r12 +  pow(R[i]-R[i+3], 2); // distanza tra elettroni
	}

	r12 = sqrt(r12); // prendo la radice dei quadrati


	//calcolo l'energia in base a quale funzione d'onda di prova scelgo
	// 0 -> wavefunction gaussiana con solo alpha e senza interazione culombiana
	// 1 -> wavefunction gaussiana con solo alpha e con interazione culombiana
	// 2 -> wavefunction con due parametri e interazione culombiana

	// solo interazione culombiana

	Eloc = 0.5*pow(omega, 2)*(r1 + r2)*(1 - pow(alpha, 2)) + 3 * alpha*omega; // Nota che r1 e r2 sono gi� al quadrato

	if (wftype == 0) {
		return Eloc;
	}

	Eloc = Eloc + 1/r12; // aggiungo interazione coulumbiana

	if (wftype == 1) {		
		return Eloc;
	}
	
	Eloc = Eloc + 0.5/pow(1+beta*r12, 2)*(alpha*omega*r12 - 0.5*pow(1+beta*r12, 2) - 2/r12 + 2*beta/(1+beta*r12));
	// aggiungo termine che viene dalla correlazione   

	if (wftype == 2) {		
		return Eloc;
	}

	
	// non ritorno niente se non setto il valore di wftype 
	// in questo modo ci accorgiamo dell'errore
	
}