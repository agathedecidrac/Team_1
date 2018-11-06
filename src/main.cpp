#include "simulation.h"
#include <string>
int main(int argc, char** argv) {
	
	try{
		Simulation sim(argc, argv);
		sim.run();
	} catch (const std::string& str) {
		std::cerr << "Error : " << str << std::endl;
	}
	
	return 0;
}
