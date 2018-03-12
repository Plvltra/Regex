#pragma once

#include <string>
#include "Node.h"

namespace Arithmetic
{
	struct Node
	{
		char symbol;
		int num;
		Node* lchild;
		Node* rchild;
		Node() = default;
		Node(char symbol, Node* lchild, Node* rchild)
			: symbol(symbol), lchild(lchild), rchild(rchild)
		{
		}
		Node(int num) : num(num), lchild(NULL), rchild(NULL) {}
	};

	// Tools
	bool isTermOp(char c);
	bool isExprOp(char c);
	std::string quoted(std::string s);
	std::string quoted(char c);
	void error(const std::string& src, int index, std::string want, std::string got);

	Node* parseNum(const std::string& pattern, int& index);
	Node* parseTerm(const std::string& pattern, int& index);
	Node* parseExpr(const std::string& pattern, int& index);
	Node* parseArithm(const std::string& pattern); // parse总表达式

	Node* calc(Node* root);
	void test();
}
