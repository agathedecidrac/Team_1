#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <iostream>
#include <string>
#include "fileManager.h"

const int SIMULATION_DEFAULT_POP_SIZE(100);
const int SIMULATION_DEFAULT_DURATION(10);
const int SIMULATION_DEFAULT_REPEATS(2);
const std::vector<double> SIMULATION_DEFAULT_FREQUENCES(std::vector<double>({0.8}));
//const int SIMULATION_DEFAULT_NB_ALLELES(2);

class Simulation {

public:
	// CONTROLLER
	Simulation(int, char**);
	~Simulation();
	
	void run();
	void setDebugMode(bool b) { mDebugMode = b; }
	
	// VIEW
	

private:
	// MODEL
	std::vector<int> mCurrentAlleles;
	int mPopulationSize; // pop size is constant -> better to store it
	int mDuration, mNbRepeats;
	
	
	// methods
	void step();
	void initialize(int nb_repeats, int duration, int pop_size, 
					const std::vector<double> &frequences, std::string);
	std::vector<double> getFrequences() const;
	
	// debug
	bool mDebugMode;
	void print(int, int, const std::vector<double>&) const;
	
	//FileManager
	//bool use_file;
	BufferManager *m_Buffer;
};

#endif // SIMULATION_H

