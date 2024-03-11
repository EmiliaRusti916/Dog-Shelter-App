#pragma once
#include <vector>
#include <string>
#include "dog.h"

using namespace std;

class DogException {
private:
	vector<string> errors;

public:
	DogException(vector<string> _errors);
	vector<string> getErrors() const;

};

class DogValidator {
public:
	DogValidator() = default;
	static void validate(const Dog& dog);


};