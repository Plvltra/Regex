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
	// ����ǰ�պ�
	// return: -1��ʾ������ƥ��
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
