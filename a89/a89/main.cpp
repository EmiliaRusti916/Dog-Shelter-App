#include "a89.h"
#include <QtWidgets/QApplication>
#include "fileAdoptionList.h"
#include "fileRepository.h"
#include "service.h"
#include "HTMLAdoptionList.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	FileRepository repo("Dogs.txt");
	FileAdoptionList* adoptionList = nullptr;
	adoptionList = new HTMLAdoptionList{ "adoptionList.html" };
	Service service(repo, adoptionList, DogValidator{});
	a89 w{ service };
    w.show();
    return a.exec();
}
