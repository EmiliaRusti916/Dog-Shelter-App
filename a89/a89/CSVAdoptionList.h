
#pragma once
#include "fileAdoptionList.h"
#include <iostream>

class CSVAdoptionList :public FileAdoptionList {
public:
    CSVAdoptionList(const string& fileName) : FileAdoptionList(fileName) {};
    ~CSVAdoptionList() {};
    void writeToFile() override;
    void displayAdoptionList()override;
};

