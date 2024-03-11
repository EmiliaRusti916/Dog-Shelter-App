#include "service.h"
#include <algorithm>
#include <iterator>
#include "HTMLAdoptionList.h"
#include "repositoryException.h"

using namespace std;

/*void Service::add10Dogs()
{
	this->addDogToRepository("Bulldog", "Rex", 3, "https://www.pexels.com/photo/white-short-coated-dog-160846/");
	this->addDogToRepository("German Shephard", "Max", 2, "https://www.pexels.com/photo/brown-german-shepherd-2695827/");
	this->addDogToRepository("Labrador Retriever", "Cooper", 1, "https://www.pexels.com/photo/photo-of-dog-sitting-on-grass-3039080/");
	this->addDogToRepository("Golden Retriever", "Bella", 6, "https://www.pexels.com/photo/photo-of-golden-retriever-sitting-on-grass-2409503/");
	this->addDogToRepository("Siberian Husky", "Charlie", 4, "https://www.pexels.com/photo/black-and-white-siberian-husky-3715587/");

	this->addDogToRepository("Poodle", "Daisy", 3, "https://www.pexels.com/photo/photo-of-a-white-furry-poodle-on-a-yellow-surface-7516820/");
	this->addDogToRepository("German Shephard", "Bailey", 5, "https://www.pexels.com/photo/adult-german-shepherd-lying-on-ground-333083/");
	this->addDogToRepository("Poodle", "Luna", 1, "https://www.pexels.com/photo/a-poodle-on-fallen-leaves-9833869/");
	this->addDogToRepository("Maltese", "Teddy", 3, "https://www.pexels.com/photo/tricolor-maltese-puppy-1458925/");
	this->addDogToRepository("Pomeranian", "Lucy", 2, "https://www.pexels.com/photo/brown-pomeranian-puppy-on-green-grass-9354308/");
}
*/

void Service::addDog(string const& breed, string const& name, int age, string const& photo)
{
	Dog dog(breed, name, age, photo);
	this->validator.validate(dog);
	this->repository.addDog(dog);
}

void Service::deleteDog(string const& breed, string const& name, int age, string const& photo)
{
	Dog dog(breed, name, age, photo);
	this->validator.validate(dog);
	this->repository.deleteDog(dog);
}

void Service::updateDog(string const& breed, string const& name, int age, string const& photo, int newAge)
{
	Dog dog(breed, name, age, photo);
	this->repository.updateDog(dog, newAge);
}

int Service::size() const
{
	return this->repository.size();
}

void Service::addDogToAdoptionList(Dog& dog)
{
	if (this->adoptionList == nullptr)
		return;
	vector<Dog> adopted = this->getAdoptionList();
	for (auto d : adopted)
		if (d.getBreed() == dog.getBreed() && d.getName() == dog.getName())
			throw std::exception("Dog already in adoption list");
	this->adoptionList->add(dog);
	this->saveAdoptionList();
}

void Service::deleteDogFromAdoptionList(string const& breed, string const& name)
{
	this->adoptionList->deleteDog(breed, name);
	this->saveAdoptionList();
}

vector<Dog>& Service::getRepository()
{
	return this->repository.getAllDogs();
}

vector<Dog>& Service::getAdoptionList()
{
	return this->adoptionList->getAdoptedDogs();
}


void Service::saveAdoptionList()
{
	if (this->adoptionList == nullptr)
		return;
	this->adoptionList->writeToFile();
}

vector<Dog> Service::filterByBreed(string const& breed)
{
	vector<Dog> filteredDogs;
	auto allDogs = this->getRepository();
	for (const auto& dog : allDogs)
		if (dog.getBreed() == breed)
			filteredDogs.push_back(dog);
	return filteredDogs;
}

void Service::setHTMLAdoptionList()
{
	this->adoptionList = new HTMLAdoptionList{ "adoptionList.html" };
}

void Service::displayAdoptionList()
{
	this->adoptionList->displayAdoptionList();
}
