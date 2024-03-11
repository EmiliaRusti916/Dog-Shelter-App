#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_a89.h"
#include "service.h"
#include <QMainWindow>
#include <QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QCheckBox>
#include <QtWidgets/QMainWindow>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <qlayout.h>
#include <qlabel.h>
#include <QFormLayout>


class a89 : public QMainWindow
{
    Q_OBJECT

private:
    Service& service;
    Ui::a89Class ui;
	QWidget* adminWindow;
	QWidget* userWindow;
	QWidget *filterWindow;
	QLabel* mainMenuLabel, * adminMenuLabel, * userMenuLabel, * currentDog;
	QPushButton* adminModeButton, * userModeButton, *submitButton;
	QLineEdit* dogBreedInput, * dogNameInput, * dogAgeInput, * dogPhotographInput, *filterBreedInput, *newAgeInput;

	QListWidget* dogsList;
	QCheckBox * adoptionListType;

	vector<Dog> filteredDogsByBreed;

	int currentIndex;

	void populate(QListWidget* itemsList, vector<Dog> dogs);

private slots:
	void setMainMenuLayout();
	void setAdminLayout();
	void setUserLayout();
	void setLayout();
	void validateBreed();
	void addDog();
	void updateDog();
	void deleteDog();
	void addDogToAdoptionList();
	void getNextDogFromAdoptionList();
	void deleteDogFromAdoptionList();
	void displayAdoptionList();
	int getSelectedIndex();

public:
	a89(Service& service, QWidget* parent = nullptr);
	~a89();
};
