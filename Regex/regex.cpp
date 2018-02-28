#include <string>
#include <iostream>
#include <stack>

#include "regex.h"
using namespace std;

Regex::Regex(const string &pattern)
{
	this->pattern = pattern;
}