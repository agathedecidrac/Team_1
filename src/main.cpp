#include "simulation.h"
#include <string>
int main(int argc, char** argv) {
	
	try{
		Simulation sim(argc, argv);
		sim.run();
	} catch (const std::string& str) {
		std::cerr << "Error : " << str << std::endl;
	}
	catch(const std::invalid_argument& arg) {
		std::cerr << "Invalid argument : " << arg.what() << std::endl;
	}
	
	return 0;
}
