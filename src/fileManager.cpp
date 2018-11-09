#include "fileManager.h"


FileManager::FileManager(string name) 
	: file_name(name) 
{}

void FileManager::print_on_buffer(vector<double>, int num_gen) {
	ifstream gen_file (file_name, ios::in); //attention à la position du fichier ?
	
	if (gen_file) {
		//Écrire dans le fichier
	} else {
		std::cerr<< "Impossible to open file named :" << file_name << std::endl;
		
	} //Est ce qu'on veut que la simulation s'arrete si on ne peut pas ouvrir le fichier ? 
	
}
