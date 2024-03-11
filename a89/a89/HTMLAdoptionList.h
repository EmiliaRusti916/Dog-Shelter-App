#pragma once
#include "fileAdoptionList.h"

class HTMLAdoptionList :public FileAdoptionList {
public:
    HTMLAdoptionList(const std::string& fileName) : FileAdoptionList(fileName) {};
    ~HTMLAdoptionList() {};
    void writeToFile() override;
    void displayAdoptionList() override;

};