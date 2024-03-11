#pragma once
#include <stdexcept>
#include <vector>
#include <algorithm>
#include "dog.h"

using namespace std;

class Repository {
protected:
    vector<Dog> dogs;
public:
    Repository();
    ~Repository();

    virtual void addDog(Dog dog);
    virtual void deleteDog(Dog dog);
    virtual bool searchDog(Dog dog);
    virtual void updateDog(Dog dog, int newAge);
    Dog& operator[](int index);
    Repository& operator=(const Repository& other);
    virtual vector<Dog>& getAllDogs();
    virtual int size() const;
    bool isEmpty() const;
};