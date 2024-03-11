
#include "CSVAdoptionList.h"
//#include "Windows.h"
//#include "fstream"
#include "repositoryException.h"

void CSVAdoptionList::writeToFile()
{
	/*ofstream file(this->filename);
	if (!file.is_open())
		throw FileException("The file could not be opened!");
	for (auto& dog : this->adoptedDogs)
	{
		file << dog;
	}

	file.close();*/
}

void CSVAdoptionList::displayAdoptionList()
{
	//ShellExecuteA(NULL, "open", "C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE", this->filename.c_str(), NULL, SW_SHOWMAXIMIZED);
}
