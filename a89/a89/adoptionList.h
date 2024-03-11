#pragma once
#include <vector>
#include "dog.h"

using namespace std;

class AdoptionList {
protected:
	vector<Dog> adoptedDogs;
	int current;

public:
	AdoptionList();
	void add(const Dog& dog);
	Dog getCurrent();
	void display();
	void next();
	bool isEmpty();
	virtual ~AdoptionList() {}
	vector<Dog>& getAdoptedDogs();
	void deleteDog(string const& breed, string const& name);
};