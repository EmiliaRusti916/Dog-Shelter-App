#include "repository.h"
#include <fstream>
#include <algorithm>
#include "dog.h"
using namespace std;

Repository::Repository() = default;

Repository::~Repository() = default;

void Repository::addDog(Dog dog)
{
	if (!this->searchDog(dog))
		this->dogs.push_back(dog);
	else
		throw std::runtime_error("Dog already in repository.");
}

void Repository::deleteDog(Dog dog)
{

	if (!this->searchDog(dog))
		throw std::runtime_error("Dog not found.");

	this->dogs.erase(std::remove(this->dogs.begin(), this->dogs.end(), dog), this->dogs.end());
}

bool Repository::searchDog(Dog dog)
{
	auto iterator = std::find(this->dogs.begin(), this->dogs.end(), dog);
	return iterator != this->dogs.end();
}

void Repository::updateDog(Dog dog, int newAge)
{
	if (!this->searchDog(dog))
		throw std::runtime_error("Dog not found.");
	else {
		for (Dog& currentDog : this->dogs)
			if (currentDog.getName() == dog.getName() && currentDog.getBreed() == dog.getBreed()) {
				currentDog.setAge(newAge);
			}
	}
}

Dog& Repository::operator[](int index)
{
	if (index >= this->dogs.size())
		throw std::runtime_error("Index not in vector!");
	return this->dogs[index];
}

Repository& Repository::operator=(const Repository& other)
{
	if (this == &other)
		return *this;
	this->dogs = other.dogs;
	return *this;
}

vector<Dog>& Repository::getAllDogs()
{
	return this->dogs;
}

int Repository::size() const
{
	return this->dogs.size();
}

bool Repository::isEmpty() const
{
	return this->dogs.empty();
}
