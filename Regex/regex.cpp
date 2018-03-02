#include "Regex.h"

using namespace std;

Regex::Regex(string pattern)
	: _pattern(pattern), _index(0)
{
	buildTree();
}