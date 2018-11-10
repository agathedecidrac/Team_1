#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

const std::string FILEMANAGER_DEFAULT_BUFFER_FILE_NAME("buffer");

/* Collecter les résultats de la simulation
 * les deverser dans un fichier (buffer)
 *  */

class FileManager {
public:
	FileManager();
	~FileManager();

private: 
		
protected:
	static bool existingFile(const std::string &f_name);
};

// héritage en private pour l'instant : on utilise le buffer très différement d'un fichier normal
class BufferManager : private FileManager {
	
public:
	// CONTROLLER
	BufferManager();
	~BufferManager();

	void openBuffer();
	// clear the and returns the content of the file
	std::string clearBuffer();
	void print_in(const std::vector<double>&);
	
	// VIEW
	bool isOpen() const;

private:
	std::ofstream m_Output;
	std::string m_FileName;
};

#endif
