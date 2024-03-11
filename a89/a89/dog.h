#pragma once
#include <string>
#include <iostream>
#include <Windows.h>
#include <shellapi.h>
using std::string;

class Dog
{
private:
	string breed;
	string name;
	int age;
	string photograph;

public:
	//Default constructor
	Dog();
	//Parameters contructor
	Dog(string const& breed, string const& name, int age, string const& photograph);
	//Copy constructor
	Dog(const Dog& other);
	//destructor for Dog
	~Dog();
	string getBreed() const;
	string getName() const;
	int getAge() const;
	string getPhotograph() const;
	bool operator==(const Dog& other) const;
	bool operator!=(const Dog& other);
	string toString() const;
	void setAge(int newAge);
	void setPhoto(string const& newPhoto);

	void display();

	friend std::istream& operator>>(std::istream& is, Dog& dog);
	friend std::ostream& operator<<(std::ostream& os, const Dog& dog);
};
