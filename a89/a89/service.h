#pragma once
#include "dog.h"
#include "fileRepository.h"
#include "fileAdoptionList.h"
#include "dogValidator.h"

class Service {

private:
    FileRepository& repository;
    FileAdoptionList* adoptionList;
    DogValidator validator;

public:
    Service(FileRepository& repository, FileAdoptionList* adoptionList, DogValidator validator) : repository{ repository }, adoptionList{ adoptionList }, validator{ validator } {}
    ~Service() {}
    FileAdoptionList* getAdoptionList() const { return adoptionList; }
    void addDog(string const& breed, string const& name, int age, string const& photo);
    void deleteDog(string const& breed, string const& name, int age, string const& photo);
    void updateDog(string const& breed, string const& name, int age, string const& photo, int newAge);
    int size() const;
    void addDogToAdoptionList(Dog& dog);
    void deleteDogFromAdoptionList(string const& breed, string const& name);
    vector<Dog>& getRepository();
    vector<Dog>& getAdoptionList();
    void saveAdoptionList();
    vector<Dog> filterByBreed(string const& breed);
    void setHTMLAdoptionList();
    void displayAdoptionList();
};
