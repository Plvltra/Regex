#pragma once
#include <string>
#include <memory>

#include "EpsilonNFA.h"
#include "Node.h"
#include "Graph.h"

class Regex
{
public:
	// Construtors
	Regex(std::string pattern);
	// Functions
	void printTree();
	// 返回前闭后开
	// return: -1表示不存在匹配
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
	NodePtr parseA();
	NodePtr parseB();
	NodePtr parseC();
	NodePtr parseD();
	NodePtr parseE();
	NodePtr parseF();
	GraphPtr buildGraph(NodePtr root);

	Type currToken();
	Type nextToken();
};
