#include "a89.h"
#include <QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLineEdit>
#include <QMessageBox>
#include <QStringList>
#include "utils.h"
#include "repositoryException.h"

a89::a89(Service& service, QWidget* parent)
	: QMainWindow(parent), service{ service }
{
	adminWindow = nullptr;
	userWindow = nullptr;

	setMainMenuLayout();
}

void a89::setMainMenuLayout()
{
	if (adminWindow != nullptr)
		adminWindow->hide();

	if (userWindow != nullptr)
		userWindow->hide();

	mainMenuLabel = new QLabel{ "Select mode(Admin/User) and File : " };

	QFont mainMenuFont;
	mainMenuFont.setPixelSize(20);
	mainMenuLabel->setFont(mainMenuFont);

	userModeButton = new QPushButton{ "User" };
	adminModeButton = new QPushButton{ "Admin" };

	connect(userModeButton, &QPushButton::clicked, this, &a89::setLayout);
	connect(adminModeButton, &QPushButton::clicked, this, &a89::setAdminLayout);

	adoptionListType = new QCheckBox{ "HTML Adoption List" };

	QWidget* centralWidget = new QWidget{};

	QVBoxLayout* mainLayout = new QVBoxLayout{ centralWidget };
	QHBoxLayout* buttonsLayout = new QHBoxLayout{};

	mainLayout->addWidget(mainMenuLabel);

	buttonsLayout->addWidget(adminModeButton);
	buttonsLayout->addWidget(userModeButton);
	buttonsLayout->addWidget(adoptionListType);

	mainLayout->addLayout(buttonsLayout);

	this->setCentralWidget(centralWidget);
	this->show();
}

a89::~a89()
{}

void a89::populate(QListWidget* itemsList, vector<Dog> dogs)
{
	itemsList->clear();
	for (const auto& dog : dogs)
		itemsList->addItem(QString::fromStdString(dog.toString()));
}

void a89::setAdminLayout()
{
	this->hide();

	adminWindow = new QWidget{};
	adminWindow->setWindowTitle("Admin Mode");

	dogsList = new QListWidget{ adminWindow };
	this->populate(dogsList, this->service.getRepository());

	QHBoxLayout* dogsListLayout = new QHBoxLayout{};
	dogsListLayout->addWidget(dogsList);

	// create form layout for tutorial input
	QFormLayout* dogForm = new QFormLayout{};

	QLabel* dogBreedLabel = new QLabel{ "Breed:" };
	dogBreedInput = new QLineEdit{};

	dogForm->addRow(dogBreedLabel, dogBreedInput);


	QLabel* dogNameLabel = new QLabel{ "Name:" };
	dogNameInput = new QLineEdit{};

	dogForm->addRow(dogNameLabel, dogNameInput);


	QLabel* dogAgeLabel = new QLabel{ "Age:" };
	dogAgeInput = new QLineEdit{};

	dogForm->addRow(dogAgeLabel, dogAgeInput);


	QLabel* dogPhotographLabel = new QLabel{ "Photograph:" };
	dogPhotographInput = new QLineEdit{};

	dogForm->addRow(dogPhotographLabel, dogPhotographInput);

	QLabel* dogNewAgeLabel = new QLabel{ "New Age:" };
	newAgeInput = new QLineEdit{};
	dogForm->addRow(dogNewAgeLabel, newAgeInput);

	QVBoxLayout* editLayout = new QVBoxLayout{};
	editLayout->addLayout(dogForm);

	// create buttons for add, remove and update
	QPushButton* addDogButton, * updateDogButton, * deleteDogButton;
	addDogButton = new QPushButton{ "Add" };
	updateDogButton = new QPushButton{ "Update" };
	deleteDogButton = new QPushButton{ "Delete" };

	connect(addDogButton, &QPushButton::clicked, this, &a89::addDog);
	connect(updateDogButton, &QPushButton::clicked, this, &a89::updateDog);
	connect(deleteDogButton, &QPushButton::clicked, this, &a89::deleteDog);


	QHBoxLayout* optionsLayout = new QHBoxLayout{};
	optionsLayout->addWidget(addDogButton);
	optionsLayout->addWidget(updateDogButton);
	optionsLayout->addWidget(deleteDogButton);

	editLayout->addLayout(optionsLayout);

	QHBoxLayout* mainLayout = new QHBoxLayout{ adminWindow };

	mainLayout->addLayout(dogsListLayout);
	mainLayout->addLayout(editLayout);

	adminWindow->setLayout(mainLayout);
	adminWindow->show();
}

void a89::setUserLayout()
{
	this->hide();
	this->filterWindow->hide();
	this->service.setHTMLAdoptionList();

	this->userWindow = new QWidget{};
	userWindow->setWindowTitle("User mode");

	dogsList = new QListWidget{ userWindow };
	this->populate(dogsList, this->service.getAdoptionList());

	QLabel* dogsListLabel = new QLabel{ "Adoption list:" };
	QVBoxLayout* adoptionListDisplayLayout = new QVBoxLayout{};

	adoptionListDisplayLayout->addWidget(dogsListLabel);
	adoptionListDisplayLayout->addWidget(dogsList);	

	string requiredBreed = this->filterBreedInput->text().toStdString();

	this->filteredDogsByBreed = this->service.filterByBreed(requiredBreed);
	Dog firstDog = this->filteredDogsByBreed[0];
	currentIndex = 0;

	QLabel* currentDogIndicatorLabel = new QLabel{ "Current Dog: " };
	currentDog = new QLabel{ QString::fromStdString(firstDog.toString())};

	// layout for current tutorial
	QHBoxLayout* currentDogLayout = new QHBoxLayout{};
	currentDogLayout->addWidget(currentDogIndicatorLabel);
	currentDogLayout->addWidget(currentDog);

	QPushButton* addToWatchListButton = new QPushButton{ "Add" };
	QPushButton* nextTutorialButton = new QPushButton{ "Next" };
	QPushButton* deleteFromWatchListButton = new QPushButton{ "Delete" };
	QPushButton* openWatchListButton = new QPushButton{ "Open" };

	connect(addToWatchListButton, &QPushButton::clicked, this, &a89::addDogToAdoptionList);
	connect(nextTutorialButton, &QPushButton::clicked, this, &a89::getNextDogFromAdoptionList);
	connect(deleteFromWatchListButton, &QPushButton::clicked, this, &a89::deleteDogFromAdoptionList);
	connect(openWatchListButton, &QPushButton::clicked, this, &a89::displayAdoptionList);

	QGridLayout* optionsLayout = new QGridLayout{};
	optionsLayout->addWidget(addToWatchListButton, 0, 0);
	optionsLayout->addWidget(nextTutorialButton, 1, 0);
	optionsLayout->addWidget(deleteFromWatchListButton, 0, 1);
	optionsLayout->addWidget(openWatchListButton, 1, 1);

	// set up watch list management layout
	QVBoxLayout* adoptionListManagementLayout = new QVBoxLayout{};
	adoptionListManagementLayout->addLayout(currentDogLayout);
	adoptionListManagementLayout->addLayout(optionsLayout);

	QHBoxLayout* mainLayout = new QHBoxLayout{ userWindow };
	mainLayout->addLayout(adoptionListDisplayLayout);
	mainLayout->addLayout(adoptionListManagementLayout);


	userWindow->show();
}

void a89::setLayout()
{
	this->hide();

	filterWindow = new QWidget{};
	filterWindow->setWindowTitle("Filter by breed:");
	filterWindow->resize(300, 200);

	QLabel* filterLabel = new QLabel{ "Enter breed to search for:" };
	filterBreedInput = new QLineEdit{};
	QFormLayout* breedInputLayout = new QFormLayout{};
	breedInputLayout->addRow(filterLabel, filterBreedInput);

	submitButton = new QPushButton{ "Submit Breed." };
	connect(submitButton, &QPushButton::clicked, this, &a89::validateBreed);

	QVBoxLayout* mainLayout = new QVBoxLayout{ filterWindow };
	mainLayout->addLayout(breedInputLayout);
	mainLayout->addWidget(submitButton);

	filterWindow->show();
}

void a89::validateBreed()
{
	string breed = this->filterBreedInput->text().toStdString();

	if (service.filterByBreed(breed).size() == 0)
	{
		QMessageBox errorDisplay;
		errorDisplay.setText("There is no dog with required breed!");
		errorDisplay.setWindowTitle("No dog found!");
		errorDisplay.exec();
	}

	else
		this->setUserLayout();
}

void a89::addDog()
{
	string breed = this->dogBreedInput->text().toStdString();
	string name = this->dogNameInput->text().toStdString();
	int age = stoi(this->dogAgeInput->text().toStdString());
	string photo = this->dogPhotographInput->text().toStdString();

	try
	{
		this->service.addDog(breed, name, age, photo);

		this->populate(dogsList, this->service.getRepository());
	}

	catch (DogValidator& ve)
	{
		QMessageBox::critical(this, "Error on dog validation", "Invalid input.");
		return;
	}

	catch (RepositoryException& re)
	{
		QMessageBox::critical(this, "Error in repository", "Repository exception.");
		return;
	}

}

void a89::updateDog()
{
	string breed = this->dogBreedInput->text().toStdString();
	string name = this->dogNameInput->text().toStdString();
	int age = stoi(this->dogAgeInput->text().toStdString());
	string photo = this->dogPhotographInput->text().toStdString();
	int newAge = stoi(this->newAgeInput->text().toStdString());
	try
	{
		this->service.updateDog(breed, name, age, photo, newAge);

		this->populate(dogsList, this->service.getRepository());
	}

	catch (DogValidator& ve)
	{
		QMessageBox::critical(this, "Error on dog validation", "Invalid input.");
		return;
	}

	catch (RepositoryException& re)
	{
		QMessageBox::critical(this, "Error in repository", "Repository exception.");
		return;
	}
}

void a89::deleteDog()
{
	string breed = this->dogBreedInput->text().toStdString();
	string name = this->dogNameInput->text().toStdString();
	int age = stoi(this->dogAgeInput->text().toStdString());
	string photo = this->dogPhotographInput->text().toStdString();

	try
	{
		this->service.deleteDog(breed, name, age, photo);

		this->populate(dogsList, this->service.getRepository());
	}

	catch (DogValidator& ve)
	{
		QMessageBox::critical(this, "Error on dog validation", "Invalid input.");
		return;
	}

	catch (RepositoryException& re)
	{
		QMessageBox::critical(this, "Error in repository", "Repository exception.");
		return;
	}
}

void a89::addDogToAdoptionList()
{
	Dog tutorialToAdd = this->filteredDogsByBreed[currentIndex];

	try
	{
		this->service.addDogToAdoptionList(tutorialToAdd);
		this->populate(dogsList, this->service.getAdoptionList());
	}
	catch (RepositoryException& re)
	{
		QMessageBox::critical(this, "Error in repository", "Repository exception.");
		return;
	}
	catch (exception)
	{
		QMessageBox::critical(this, "Error in repository", "Dog already in adoption list.");
		return;
	}
}

void a89::getNextDogFromAdoptionList()
{
	currentIndex = (currentIndex + 1) % this->filteredDogsByBreed.size();
	Dog currentDog = this->filteredDogsByBreed[currentIndex];

	this->currentDog->setText(QString::fromStdString((currentDog.toString())));
}

void a89::deleteDogFromAdoptionList()
{
	int index = this->getSelectedIndex();
	if (index == -1)
	{
		QMessageBox::critical(this, "Error", "No dog was selected.");
		return;
	}
	Dog dog = this->service.getAdoptionList()[index];
	this->service.deleteDogFromAdoptionList(dog.getBreed(), dog.getName());
	this->populate(dogsList, this->service.getAdoptionList());
}

void a89::displayAdoptionList()
{
	this->service.displayAdoptionList();
}

int a89::getSelectedIndex()
{
	QModelIndexList indexList = this->dogsList->selectionModel()->selectedIndexes();
	if (indexList.size() == 0)
		return -1;
	return indexList[0].row();
}
