#include <exception>
#include <iostream>

#include "Regex.h"
#include "GraphManager.h"

using namespace std;

Regex::Regex(string pattern)
	: pattern(pattern), index(0)
{
	if (pattern == "")
		throw exception("模式为空");
	bool debug = false;
	_root = parse();
	if (debug) _root->rowOrderPrint(); 
	graph = buildGraph(_root); 
	if (debug) graph->printGraph();
	nfaGraph = makeNFAGraph(graph); 
	if (debug) nfaGraph->printGraph();
	dfaGraph = makeDFAGraph(nfaGraph);
	if (debug) dfaGraph->printGraph();
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
	NodePtr root = parseA();
	// return root;
	if (currToken() != '\0') 
		throw exception("待匹配串有多余部分");
	else 
		return root;
}

// A = A '|' B
// A = B
NodePtr Regex::parseA()
{
	if (currToken() == '|' || currToken() == '+' || currToken() == '*' 
		|| currToken() == '?' || currToken() == ')' || currToken() == ']')
		throw exception("匹配表达式A中符号出现在错误的位置");
	NodePtr lchild = parseB();
	NodePtr root = lchild;
	while (currToken() != '\0' && currToken() == '|')
	{
		nextToken();
		if (currToken() == '\0')
			throw exception("表达式非法结束，| 操作符缺少右操作数");
		else if (currToken() == '|' || currToken() == '+' || currToken() == '*' 
			|| currToken() == '?' || currToken() == ')' || currToken() == ']')
			throw exception("表达式非法结束，| 操作符非法连接右操作数 ");
		NodePtr rchild = parseB();
		root = makeNode('|', lchild, rchild);
		lchild = root;
	}
	return root;
}

// B = BC
// B = C
NodePtr Regex::parseB()
{
	NodePtr lchild = parseC();
	NodePtr root = lchild;
	while (currToken() != '\0' && currToken() != '|'
		&& currToken() != '+' && currToken() != '*' 
		&& currToken() != '?' && currToken() != ')' && currToken() != ']')
	{
		NodePtr rchild = parseC();
		root = makeNode('&', lchild, rchild);
		lchild = root;
	}
	return root;
}

// C = C '+'
// C = C '*'
// C = C '?'
// C = '(' A ')'
// C = D
NodePtr Regex::parseC()
{
	NodePtr root = NULL;
	if (currToken() == '(') //匹配 '(' A ')'
	{
		nextToken();
		NodePtr child = parseA();
		root = child;
		char expected = currToken();
		nextToken();
		if (expected != ')')
			throw exception("括号不匹配");
		// C = '(' A ')', 额外匹配 C '*'之类
		while (currToken() != '\0'
			&& (currToken() == '+' || currToken() == '*' || currToken() == '?'))
		{
			root = makeNode(currToken(), child);
			child = root;
			nextToken();
		}
	}
	else
	{
		NodePtr child = parseD(); //匹配  D
		root = child;
		// TODO: debug
		// 额外匹配  D '*', ( D '+') '*'
		while (currToken() != '\0' 
			&& (currToken() == '+' || currToken() == '*' || currToken() == '?'))
		{
			root = makeNode(currToken(), child);
			child = root;
			nextToken();
		}
	}	
	return root;
}

// D = char
// D = '\' char
// D = '[' E ']'
// D = "[^" E ']'
NodePtr Regex::parseD()
{
	return parseE();
}

// E = EF
// E = F
NodePtr Regex::parseE()
{
	return parseF();
}

// F = char '-' char
// F = char
// F = '\' char
NodePtr Regex::parseF()
{
	// TODO: implements
	char token = pattern[index++];
	return makeNode(token);
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

Type Regex::currToken()
{
	return pattern[index];
}

Type Regex::nextToken()
{
	return pattern[++index];
}