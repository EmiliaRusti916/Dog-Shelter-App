#include "adoptionList.h"

AdoptionList::AdoptionList()
{
	this->current = 0;
}

void AdoptionList::add(const Dog& dog)
{
	this->adoptedDogs.push_back(dog);
}

Dog AdoptionList::getCurrent()
{
	if (this->current == this->adoptedDogs.size())
		this->current = 0;
	return this->adoptedDogs[this->current];
}

void AdoptionList::display()
{
	if (this->adoptedDogs.size() == 0)
		return;
	Dog currentDog = this->getCurrent();
	currentDog.display();
}

void AdoptionList::next()
{
	if (this->adoptedDogs.size() == 0)
		return;
	this->current++;
	Dog currentDog = this->getCurrent();
	currentDog.display();
}

bool AdoptionList::isEmpty()
{
	return this->adoptedDogs.size() == 0;
}

vector<Dog>& AdoptionList::getAdoptedDogs()
{
	return this->adoptedDogs;
}

void AdoptionList::deleteDog(string const& breed, string const& name)
{
	int index = 0;
	for (const auto& dog : this->adoptedDogs)
	{
		if (dog.getBreed() == breed && dog.getName() == name)
			break;
		index++;
	}
	if (index >= this->adoptedDogs.size())
		throw std::runtime_error("Dog not found!");
	this->adoptedDogs.erase(this->adoptedDogs.begin() + index);
}