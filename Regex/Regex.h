#pragma once
#include <string>

class Regex
{
public:
	Regex(std::string pattern);
	virtual ~Regex();

public:
	parse(const std::string& src);

private:
	std::string _pattern;
	int _index;
private:
	buildTree();
};
