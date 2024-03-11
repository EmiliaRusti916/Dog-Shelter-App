#include "dogValidator.h"

DogException::DogException(vector<string> _errors) : errors{ _errors }
{
}

vector<string> DogException::getErrors() const
{
	return this->errors;
}

void DogValidator::validate(const Dog& dog)
{
	vector<string> errors;
	if (dog.getAge() <= 0)
		errors.push_back("The age must be a natural number.\n");
	if (!isupper(dog.getName()[0]))
		errors.push_back("The name must start with a capital letter.\n");
	if (dog.getBreed().size() < 2)
		errors.push_back("The breed name cannot be less than 2 characters.\n");
	size_t posWww = dog.getPhotograph().find("www");
	size_t posHttp = dog.getPhotograph().find("http");
	if (posWww != 0 && posHttp != 0)
		errors.push_back("The photograph source must start with one of the following strings: \"www\" or \"http\"");

	if (errors.size() > 0)
		throw DogException(errors);
}
