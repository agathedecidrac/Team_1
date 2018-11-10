#include "simulation.h"
#include "fileManager.h"
#include <tclap/CmdLine.h>
#include <stdexcept>
#include <math.h>


Simulation::Simulation(int argc, char** argv) {
	TCLAP::CmdLine cmd("Population genetics simulation");
	TCLAP::ValueArg< int > pop_size("N", "size", "Number of individuals in the population", false, SIMULATION_DEFAULT_POP_SIZE, "int");
	cmd.add(pop_size);
	TCLAP::ValueArg<int> duration("d", "duration", "Number of generations created", false, SIMULATION_DEFAULT_DURATION, "int");
	cmd.add(duration);
	
	/*TCLAP::ValueArg<int> nb_alleles("a", "number_alleles", "Number of alleles in the population", false, SIMULATION_DEFAULT_NB_ALLELES, "int");
	cmd.add(nb_alleles);*/
	
	TCLAP::UnlabeledMultiArg<double> frequences("f", "frequences", "Frequence of each allele in the population", false, "double");
	cmd.add(frequences);
	TCLAP::ValueArg<int> nb_repetitions("R", "repeats", "Number of times we repeat the simulation", false, SIMULATION_DEFAULT_REPEATS, "int");
	cmd.add(nb_repetitions);
	TCLAP::SwitchArg arg_debug("D", "debug", "Activate debug mode (verbose mode)");
	cmd.add(arg_debug);
	TCLAP::ValueArg<std::string> buffer_name ("n", "file_name", "Name of file we print the generations on", false, "jv",  "string");
    cmd.add(buffer_name);
   
    cmd.parse(argc, argv);
    this->initialize(nb_repetitions.getValue(), duration.getValue(), 
					 pop_size.getValue(), frequences.getValue(), buffer_name.getValue());
    this->setDebugMode(arg_debug.getValue());
}

Simulation::~Simulation() 
{}

// initialize devrait être appelé avant cette fonction
void Simulation::run() {
	// store temporarily initial conditions across each repeat
	std::vector<int> initial_alleles_count = mCurrentAlleles;
	
	if(mDebugMode) {
		const int allele_number(initial_alleles_count.size());
		std::cout << "Simulation : " << mNbRepeats << " repeats, " << mDuration << " generations, "
				  << allele_number << " alleles, " << mPopulationSize << " individuals"
				  << "\nInitial distribution of alleles : ";
		for(int i(0); i < allele_number; i++) {
			std::cout << initial_alleles_count[i];
			if(i < allele_number-1) std::cout << ", ";
		}
		std::cout << "\n\n";
	}
		
	for(int r(0); r < mNbRepeats; r++) {
		mCurrentAlleles = initial_alleles_count;
		for(int i(0); i < mDuration; i++) {
			// ICI modifier mCurrentAlleles par des nombres générés automatiquement
			
			std::vector<double> frequences(getFrequences());
			if(mDebugMode) print(r, i, frequences);
			// graphic -> ajouter cette génération au graphe
			//ICI : DONNER LE TABLEAU DE FREQUENCES À FILE MANAGER 
		}
	}
}

// But : vérifier les arguments et initialiser les attributs
// Q: que faire si les occurences des allèles (freq * pop_size) ne sont pas des chiffres rond ?
void Simulation::initialize(int nb_repeats, int duration, int pop_size, std::vector<double> frequences, std::string buffer_name) {
	if(nb_repeats < 1) throw std::invalid_argument("Invalid number of repeats");
	if(pop_size < 1) throw std::invalid_argument("Invalid population size"); 
	if(duration < 1) throw std::invalid_argument("Duration should be at least 1");
	double sum(0);
	for(double d : frequences) {
		if(d < 0.0 or d > 1.0) throw std::invalid_argument("Invalid frequences (should be in the range 0-1)"); // error...
		sum += d;
	}
	if(sum == 0) throw std::invalid_argument("You should specify at least 1 frequence");
	if(sum > 1.0) throw std::invalid_argument("Frequences sum to more than 1");
	// Si la somme des fréq n'est pas 1, on considère qu'il existe +1 allèle de fréquence (1-sum)
	if(sum < 1.0)
		frequences.push_back( 1.0-sum );
		
	// TOUS LES PARAMETRES SONT VALIDES A CE POINT
	mPopulationSize = pop_size;
	mNbRepeats = nb_repeats;
	mDuration = duration;
	// ATTENTION: pas encore géré, si les occurences d'une allèle n'est pas un entier, cela voudrait dire que pop_size ne reflète pas le nb d'allèles en circulation
	for(double d : frequences)
		mCurrentAlleles.push_back( (int)round(d * mPopulationSize) ); //Ça devrait gérer le sous pb n°2 (comme on a deja verifié que toutes les fréquences se somment à 1, si on arrondi on devrait retomber sur un résultat acceptable 
																	  //Aussi le sous pb n°1 (l'opération d'arrondi ne modifie pas le nombre car c'est deja un pseudo-entier, et apres on la truncation le stocke comme "vrai" int)
	//FileManager
	if (buffer_name != "") {
		use_file =true;
		FileManager f (buffer_name);
	}

}

std::vector<double> Simulation::getFrequences() const {
	std::vector<double> frequences;
	for(int i : mCurrentAlleles)
		frequences.push_back((double)i / mPopulationSize);
	return frequences;
}

void Simulation::print(int r, int i, const std::vector<double>& freq) const {
	std::cout << "[R"<< r+1 << "] Gen " << i+1 << " ";
	for(double d : freq) std::cout<<"\t" << d;
	std::cout << std::endl;
}




