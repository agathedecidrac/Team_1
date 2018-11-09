#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

/* Collecter les résultats de la simulation
 * les deverser dans un fichier (buffer)
 *  */

class FileManager {
	public :
		FileManager(string);
		~FileManager();
		void print_on_buffer(vector<double>, int num_gen); //J'ai pensé que passer aussi le numero de la generation rendrait le fichier plus lisible, à voir si c'est vraiment utile au final
		
	
	
	
	
	
	
	private : 
		string file_name;
};

#endif
