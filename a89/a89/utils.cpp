#include "utils.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

std::vector<std::string> tokenize(const std::string& str, char delimiter)
{
	vector <string> result;
	stringstream ss(str);
	string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}

vector<string> split(const string str, char delimiter)
{
	vector<string> tokens;
	istringstream stringStream(str);
	string currentToken;

	while (getline(stringStream, currentToken, delimiter))
	{
		tokens.push_back(stripString(currentToken));
	}

	return tokens;
}

string stripString(string str)
{
	int firstSpace = 0, lastSpace = str.size() - 1;

	while (firstSpace < str.size() && (str[firstSpace] == ' ' || str[firstSpace] == '\n'))
		firstSpace++;

	while (lastSpace >= 0 && (str[lastSpace] == ' ' || str[lastSpace] == '\n'))
		lastSpace--;

	return str.substr(firstSpace, lastSpace - firstSpace + 1);
}
