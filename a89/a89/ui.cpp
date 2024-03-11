#include "ui.h"
#include <iostream>
#include <windows.h>
#include "repositoryException.h"

using std::cin;
using std::cout;
using std::endl;

Ui::Ui(Service& service) :
    service{ service } {

}

Ui::~Ui() = default;

void Ui::runUI()
{
    int option;
    try {
        while (true) {
            cout << "\n1. Admin" << endl;
            cout << "2. User" << endl;
            cout << "0. Exit" << endl;

            cout << "Enter wanted option: 1 for Admin, 2 for User." << endl;
            cin >> option;
            if (option == 1)
                this->runAdmin();
            else if (option == 2)
                this->runUser();
            else if (option == 0)
                break;
            else
                cout << "Invalid option!" << endl;
        }
    }
    catch (const std::runtime_error& exception) {
        cout << "Error" << endl;
    }
}

void Ui::printAdminMenu()
{
    cout << "\n0. Exit." << endl;
    cout << "1. Add a dog." << endl;
    cout << "2. Delete a dog." << endl;
    cout << "3. Update a dog." << endl;
    cout << "4. List all dogs." << endl;
}

void Ui::printDog(const Dog& dog)
{
    cout << "Breed: " << dog.getBreed() << endl;
    cout << "Name: " << dog.getName() << endl;
    cout << "Age: " << dog.getAge() << endl;
    cout << "Photograph: " << dog.getPhotograph() << endl;
    //ShellExecute(nullptr, nullptr, "chrome.exe",
       // dog.getPhotograph().c_str(), nullptr, SW_SHOWNORMAL);
}

void Ui::printChoices()
{
    cout << "1.Next" << endl;
    cout << "2.Adopt" << endl;
    cout << "3.Exit" << endl;

}

void Ui::runAdmin()
{
    int option;
    while (true) {
        cout << "Enter wanted option.";
        printAdminMenu();
        cin >> option;
        try {
            switch (option) {
            case 1:
            {
                string breed;
                string name;
                string photograph;
                int age;
                cout << "Enter breed." << endl;
                cin.ignore();
                getline(cin, breed);
                cout << "Enter name." << endl;
                getline(cin, name);
                cout << "Enter age." << endl;
                while (!(cin >> age)) {
                    cout << "\nPlease enter an integer:" << endl;
                    cin.clear();
                    cin.ignore(64, '\n');
                }
                cout << "Enter photograph." << endl;
                cin.ignore();
                getline(cin, photograph);
                try {
                    this->service.addDog(breed, name, age, photograph);

                }
                catch (DogException& e)
                {
                    for (auto d : e.getErrors())
                        cout << d;

                }
                catch (RepositoryException& e)
                {
                    cout << e.what() << endl;
                }
                catch (FileException& e)
                {
                    cout << e.what() << endl;
                }
                break;
            }

            case 2:
            {
                string breed;
                string name;
                string photograph;
                int age;
                cout << "Enter breed." << endl;
                cin.ignore();
                getline(cin, breed);
                cout << "Enter name." << endl;
                getline(cin, name);
                cout << "Enter age." << endl;
                while (!(cin >> age)) {
                    cout << "\nPlease enter an integer:" << endl;
                    cin.clear();
                    cin.ignore(64, '\n');
                }
                cout << "Enter photograph." << endl;
                cin.ignore();
                getline(cin, photograph);
                try {
                    this->service.deleteDog(breed, name, age, photograph);

                }
                catch (DogException& e)
                {
                    for (auto d : e.getErrors())
                        cout << d;

                }
                catch (RepositoryException& e)
                {
                    cout << e.what() << endl;
                }
                catch (FileException& e)
                {
                    cout << e.what() << endl;
                }
                break;
            }

            case 3:
            {
                string breed, name, newPhotograph;
                int newAge;
                string photograph;
                int age;
                cout << "Enter breed:" << endl;
                cin.ignore();
                getline(cin, breed);
                cout << "Enter name:" << endl;
                getline(cin, name);
                cout << "Enter age." << endl;
                while (!(cin >> age)) {
                    cout << "\nPlease enter an integer:" << endl;
                    cin.clear();
                    cin.ignore(64, '\n');
                }
                cout << "Enter photograph." << endl;
                cin.ignore();
                getline(cin, photograph);

                cout << "Enter new age:" << endl;
                while (!(cin >> newAge)) {
                    cout << "\nPlease enter an integer:" << endl;
                    cin.clear();
                    cin.ignore(64, '\n');
                }
                try {
                    this->service.updateDog(breed, name, age, photograph, newAge);

                }
                catch (DogException& e)
                {
                    for (auto d : e.getErrors())
                        cout << d;

                }
                catch (RepositoryException& e)
                {
                    cout << e.what() << endl;
                }
                catch (FileException& e)
                {
                    cout << e.what() << endl;
                }
                break;
            }

            case 4:
            {
                auto dogs = this->service.getRepository();
                if (dogs.empty()) {
                    cout << "There are no dogs in the repository." << endl;
                    break;
                }
                for (const auto& dog : dogs)
                    printDog(dog);
                break;
            }
            case 0:
            {
                return;
            }
            default:
            {
                cout << "Invalid option!" << endl;
                break;
            }
            }
        }
        catch (const std::runtime_error& exception) {
            cout << exception.what() << endl;
        }
    }
}

void Ui::printUserMenu()
{
    cout << "\n0. Exit." << endl;
    cout << "1. View each dog." << endl;
    cout << "2. Filter dogs by breed." << endl;
    cout << "3. View the adoption list." << endl;
    cout << "4. Save the adoption list." << endl;
}

void Ui::runUser()
{
    int option;
    while (true)
    {
        printUserMenu();
        cout << "Enter wanted option: ";
        cin >> option;
        try {
            switch (option) {
            case 0: {
                return;
            }
            case 1: {
                auto dogs = this->service.getRepository();
                if (dogs.empty()) {
                    cout << "There are no dogs in the repository.";
                    break;
                }
                auto currentDog = dogs.begin();
                while (true) {
                    printDog(*currentDog);
                    int choice;
                    while (true) {
                        printChoices();
                        cout << "Enter choice: ";
                        cin >> choice;
                        if (choice == 2) {
                            try {
                                this->service.addDogToAdoptionList(*currentDog);
                            }
                            catch (const std::runtime_error& exception) {
                                cout << exception.what() << endl;
                            }
                        }
                        else if (choice == 1 || choice == 3)
                            break;
                        else {
                            cout << "Invalid option" << endl;
                        }
                    }
                    if (choice == 3) {
                        break;
                    }
                    if (currentDog == dogs.end() - 1)
                        currentDog = dogs.begin();
                    else
                        currentDog++;
                }
                break;
            }
            case 2: {
                string breed;
                int age;
                cout << "Enter breed: " << endl;
                cin.ignore();
                getline(cin, breed);
                vector<Dog> filteredDogs = this->service.filterByBreed(breed);
                if (filteredDogs.empty() == 1)
                    cout << "No dogs of that breed in the repository." << endl;
                else {
                    for (const auto& dog : filteredDogs)
                        printDog(dog);
                }
                break;
            }
            case 3: {
                //this->service.getAdoptionList()->displayAdoptionList();
                break;
            }
            case 4:
            {
                //try {
                    //this->service.saveAdoptionList();
                    //if (this->service.getAdoptionList() == nullptr)
                    //{
                        //cout << "List cannot be displayed" << endl;
                        //return;
                    //}
                //}
                //catch (FileException& e) {
                    //cout << e.what() << endl;
                //}
                break;
            }
            default: {
                cout << "Invalid option." << endl;
                break;
            }
            }
        }
        catch (const std::runtime_error& exception) {
            cout << exception.what() << endl;
        }
    }
}
