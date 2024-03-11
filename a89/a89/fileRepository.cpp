#include "fileRepository.h"
#include "repositoryException.h"
#include <fstream>
#include <algorithm>
#include "dog.h"
using namespace std;

FileRepository::FileRepository(const string& filename)
{
	this->filename = filename;
	this->readFromFile();
}

void FileRepository::addDog(Dog dog)
{
	if (!this->searchDog(dog)) {
		this->dogs.push_back(dog);
		this->writeToFile();
	}

	else
		throw RepositoryException("Dog already in repository.");
}

void FileRepository::deleteDog(Dog dog)
{

	if (!this->searchDog(dog))
		throw RepositoryException("Dog not found.");

	this->dogs.erase(std::remove(this->dogs.begin(), this->dogs.end(), dog), this->dogs.end());
	this->writeToFile();
}

bool FileRepository::searchDog(Dog dog)
{
	auto iterator = std::find(this->dogs.begin(), this->dogs.end(), dog);
	return iterator != this->dogs.end();
}

void FileRepository::updateDog(Dog dog, int newAge)
{
	if (!this->searchDog(dog))
		throw RepositoryException("Dog not found.");
	else {
		for (Dog& currentDog : this->dogs)
			if (currentDog.getName() == dog.getName() && currentDog.getBreed() == dog.getBreed()) {
				currentDog.setAge(newAge);
			}
		this->writeToFile();
	}

}


vector<Dog>& FileRepository::getAllDogs()
{
	return this->dogs;
}

int FileRepository::size() const
{
	return this->dogs.size();
}

void FileRepository::readFromFile()
{
	ifstream file(this->filename);
	if (!file.is_open())
		throw FileException("The file could not be opened!");
	Dog dog;
	while (file >> dog)
	{
		this->dogs.push_back(dog);
	}
	file.close();
}

void FileRepository::writeToFile()
{
	ofstream file(this->filename);
	if (!file.is_open())
		throw FileException("The file could not be opened!");
	for (auto& dog : this->dogs)
	{
		file << dog;
	}

	file.close();
}