#pragma once
#include <string>

#include "Node.h"

// a*   a|b   ab
class Regex
{
public:
	Regex(std::string pattern);
	virtual ~Regex();

public:
	void printTree();

private:
	std::string pattern;
	int index;
	Node* root;

private:
	Node* parse();
	Node* parseExpr();
	Node* parseTerm();
	Node* parseCharSet();

	bool inExprSet(char);
	bool inTermSet(char);
};
