#pragma once
#include <cstdlib>
#include "dog.h"
#include <vector>
#include "repository.h"
using namespace std;
#include <fstream>

using namespace std;

class FileRepository : public Repository {
private:
    string filename;

public:
    //FileRepository();
    FileRepository(const string& filename);
    void addDog(Dog dog) override;
    void deleteDog(Dog dog) override;
    bool searchDog(Dog dog) override;
    void updateDog(Dog dog, int newAge) override;

    vector<Dog>& getAllDogs() override;
    int size() const override;

private:
    void readFromFile();
    void writeToFile();
};
