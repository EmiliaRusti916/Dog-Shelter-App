#include "Windows.h"
#include "HTMLAdoptionList.h"
#include "repositoryException.h"
#include "fstream"

void HTMLAdoptionList::writeToFile()
{
	ofstream file(this->filename);
	if (!file.is_open())
		throw FileException("File could not open.");

	file << "<!DOCTYPE html>\n";
	file << "<html>\n";
	file << "<head>\n";
	file << "\t<title>" << this->filename << "<title>\n";
	file << "</head>\n";
	file << "<body>\n";
	file << "<table border='1'>\n";
	file << "\t<tr>\n";
	file << "\t\t<td>Breed</td>\n";
	file << "\t\t<td>Name</td>\n";
	file << "\t\t<td>Age</td>\n";
	file << "\t\t<td>Photograph</td>\n";
	file << "\t</tr>\n";
	for (auto& dog : this->adoptedDogs)
	{
		file << "\t<tr>\n";
		file << "\t\t<td>" << dog.getBreed() << "</td>\n";
		file << "\t\t<td>" << dog.getName() << "</td>\n";
		file << "\t\t<td>" << dog.getAge() << "</td>\n";
		file << "\t\t<td>" << dog.getPhotograph() << "</td>\n";
		file << "\t</tr>\n";
	}
	file << "</table>\n";
	file << "</body>\n";
	file << "</html>";
	file.close();
}

void HTMLAdoptionList::displayAdoptionList()
{
	ShellExecuteA(NULL, "open", this->filename.c_str(), "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Google Chrome.lnk", NULL, SW_SHOWMAXIMIZED);
}
