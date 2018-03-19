#include <exception>
#include <iostream>

#include "Regex.h"
#include "GraphManager.h"

using namespace std;

Regex::Regex(string pattern)
	: pattern(pattern), index(0)
{
	_root = parse(); _root->rowOrderPrint();
	graph = buildGraph(_root); graph->printGraph();
	nfaGraph = makeNFAGraph(graph); nfaGraph->printGraph();
	dfaGraph = makeDFAGraph(nfaGraph); dfaGraph->printGraph();
}

void Regex::printTree()
{
	//root->inOrderPrint(); 
	_root->rowOrderPrint();
}

void Regex::match(std::string text)
{
	cout << dfaGraph->match(text) << endl;
}

// 只支持与或*，括号及字母数字
NodePtr Regex::parse()
{
	index = 0;
	NodePtr root = parseExpr();
	// return root;
	if (index != pattern.size()) 
		throw exception("待匹配串有多余部分");
	else 
		return root;
}

NodePtr Regex::parseExpr()
{
	NodePtr lchild = parseTerm();
	NodePtr root = lchild;
	while (index < pattern.size() && inExprSet(pattern[index]))
	{
		char token = pattern[index];
		NodePtr rchild = NULL;
		if (token == '|' || token == '&')
		{
			index++;
			rchild = parseTerm();
			root = makeNode(token, lchild, rchild);
			lchild = root;
		}
		else if(isalpha(token) || isdigit(token))
		{
			rchild = parseTerm();
			root = makeNode('&', lchild, rchild);
			lchild = root;
		}
		else if (token == '(')
		{
			rchild = parseCharSet();
			root = makeNode('&', lchild, rchild);
			lchild = root;
		}
	}
	return root;
}

NodePtr Regex::parseTerm()
{
	NodePtr charSet = parseCharSet();
	NodePtr root = charSet;
	while (index < pattern.size() && inTermSet(pattern[index]))
	{
		char token = pattern[index];
		if (token == '*')
		{
			index++;
			root = makeNode('*', charSet);
		}
	}
	return root;
}

NodePtr Regex::parseCharSet()
{
	char token = pattern[index];
	NodePtr charSet = NULL;
	if (token == '(')
	{
		index++;
		charSet = parseExpr();
		char expected = pattern[index++];
		if (expected != ')')
			throw exception("括号不匹配");
	}
	else
	{
		index++;
		charSet = makeNode(token);
	}
	return charSet;
}

GraphPtr Regex::buildGraph(NodePtr root)
{
	if (!root)
		throw exception("NULL");
	if (!root->isSymbol())
	{
		return makeGraph(root->getContent());
	}
	else
	{
		Type symbol = root->getContent();
		if (symbol == '&')
		{
			GraphPtr lgraph = buildGraph(root->getLchild());
			GraphPtr rgraph = buildGraph(root->getRchild());
			return GraphManager::chuanLink(lgraph, rgraph);
		}
		else if (symbol == '|')
		{
			GraphPtr lgraph = buildGraph(root->getLchild());
			GraphPtr rgraph = buildGraph(root->getRchild());
			return GraphManager::bingLink(lgraph, rgraph);
		}
		else if (symbol == '*')
		{
			GraphPtr lgraph = buildGraph(root->getLchild());
			return GraphManager::repeatLink(lgraph);
		}
		else
		{
			throw exception("Unrecognized symbol");
		}
	}
}

// a|b, a&b, (...)
inline bool Regex::inExprSet(char c)
{
	return c == '|' || c == '&' || c == '(' || inCharSet(c);
}

// a*
inline bool Regex::inTermSet(char c)
{
	return c == '*';
}

// a-z A-z 0-9
inline bool Regex::inCharSet(char c)
{
	return isalpha(c) || isdigit(c);
}
