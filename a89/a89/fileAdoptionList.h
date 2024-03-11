#pragma once
#include <iostream>
#include "dog.h"
#include "adoptionList.h"

class FileAdoptionList :public AdoptionList {
protected:
    std::string filename;
public:
    FileAdoptionList(const std::string& filename) {
        this->filename = filename;
    }
    virtual ~FileAdoptionList() {}
    virtual void writeToFile() = 0;
    virtual void displayAdoptionList() = 0;
};