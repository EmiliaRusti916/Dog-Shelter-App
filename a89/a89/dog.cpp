#include "dog.h"
#include "utils.h"
#include <assert.h>
#include <iostream>
#include <Windows.h>
#include <shellapi.h>
#include <vector>
using std::vector;

Dog::Dog()
{
	this->breed = "";
	this->name = "";
	this->age = 0;
	this->photograph = "";
}

Dog::Dog(string const& breed, string const& name, int age, string const& photograph)
{
	this->breed = breed;
	this->name = name;
	this->age = age;
	this->photograph = photograph;
}

Dog::Dog(const Dog& other)
{
	this->breed = other.breed;
	this->name = other.name;
	this->age = other.age;
	this->photograph = other.photograph;
}

Dog::~Dog() = default;

string Dog::getBreed() const
{
	return string(this->breed);
}

string Dog::getName() const
{
	return string(this->name);
}

int Dog::getAge() const
{
	return this->age;
}

string Dog::getPhotograph() const
{
	return string(this->photograph);
}

bool Dog::operator==(const Dog& other) const
{
	if (this->breed == other.breed && this->name == other.name && this->age == other.age && this->photograph == other.photograph)
		return true;
	return false;
}


bool Dog::operator!=(const Dog& other)
{
	if (*this == other)
		return false;
	return true;
}

string Dog::toString() const
{
	return string("Breed: " + this->breed + ", Name: " + this->name + ", Age: " + std::to_string(this->age) + ", Photograph: " + this->photograph);
}

void Dog::setAge(int newAge)
{
	this->age = newAge;
}

void Dog::setPhoto(string const& newPhoto)
{
	this->photograph = newPhoto;
}

void Dog::display()
{
	//ShellExecute(nullptr, nullptr, "chrome.exe",  this->getPhotograph().c_str(), nullptr, SW_SHOWNORMAL);
}

std::istream& operator>>(std::istream& is, Dog& dog)
{
	string line;
	getline(is, line);
	vector<string> tokens = tokenize(line, ',');
	if (tokens.size() != 4)
		return is;
	dog.breed = tokens[0];
	dog.name = tokens[1];
	dog.age = stoi(tokens[2]);
	dog.photograph = tokens[3];

	return is;
}

std::ostream& operator<<(std::ostream& os, const Dog& dog)
{
	os << dog.breed << "," << dog.name << "," << dog.age << "," << dog.photograph << "\n";
	return os;
}