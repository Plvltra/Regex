#pragma once
#include <string>
#include <memory>

#include "EpsilonNFA.h"
#include "Node.h"
#include "Graph.h"

// a*   a|b   ab

class Regex
{
public:
	// Construtors
	Regex(std::string pattern);
	// Functions
	void printTree();
	void match(std::string text);

private:
	// Attributes
	std::string pattern;
	int index;
	NodePtr _root;
	GraphPtr graph;
	NFAGraphPtr nfaGraph;
	DFAGraphPtr dfaGraph;
	// Functions
	NodePtr parse();
	NodePtr parseExpr();
	NodePtr parseTerm();
	NodePtr parseCharSet();
	GraphPtr buildGraph(NodePtr root);

	bool inExprSet(char);
	bool inTermSet(char);
	bool inCharSet(char);
};
