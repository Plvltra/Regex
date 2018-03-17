#pragma once
#include <string>
#include <memory>

#include "Node.h"

// a*   a|b   ab

typedef shared_ptr<Node> NodePtr;
class Regex
{
public:
	Regex(std::string pattern);

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
	bool inCharSet(char);
};
