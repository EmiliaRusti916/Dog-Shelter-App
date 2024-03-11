#pragma once
#include <string>
#include <vector>
using namespace std;

vector<string> tokenize(const string& str, char delimiter);

vector<string> split(const string str, char delimiter = ' ');

string stripString(const string str);