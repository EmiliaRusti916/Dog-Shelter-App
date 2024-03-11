#pragma once

#include "service.h"

class Ui {
private:
    Service& service;

public:
    Ui(Service& service);
    ~Ui();
    void runUI();

private:
    void runAdmin();
    void runUser();
    void printAdminMenu();
    void printUserMenu();
    void printDog(const Dog& dog);
    void printChoices();
};

