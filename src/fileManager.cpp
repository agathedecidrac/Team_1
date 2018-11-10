#include "fileManager.h"

/* RESTE À FAIRE :
 * 
 * supprimer fichier au destructeur de BufferManager
 * implémenter clearBuffer() (récupérer contenu et vider fichier)
 * décider d'un format du fichier buffer (format du texte)
 */

FileManager::FileManager()
{

}

FileManager::~FileManager()
{}

// STATIC METHODS

bool FileManager::existingFile(const std::string &f_name) {
	return (std::ifstream(f_name).good());
}

// ******************* BufferManager class

BufferManager::BufferManager() : FileManager()
{}

BufferManager::~BufferManager() {
	m_Output.close();
	//std::remove(m_FileName);
}

void BufferManager::openBuffer() {
	// dont want to overwrite other files...
	std::string buffer_file_name(FILEMANAGER_DEFAULT_BUFFER_FILE_NAME);
	for(int i(0); existingFile(buffer_file_name); i++)
		buffer_file_name = FILEMANAGER_DEFAULT_BUFFER_FILE_NAME+"_"+std::to_string(i);
	m_Output.open(buffer_file_name);
	if(!m_Output.is_open())
		throw std::string("Failed to create buffer file '"+buffer_file_name+"'");
	m_FileName = buffer_file_name;
}

std::string BufferManager::clearBuffer() {
	return "";
}

void BufferManager::print_in(const std::vector<double>&v) {
	m_Output<< "test\n";
}

bool BufferManager::isOpen() const {
	return m_Output.is_open();
}
