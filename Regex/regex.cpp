#include <exception>
#include <iostream>

#include "Regex.h"

using namespace std;

Regex::Regex(string pattern)
	: pattern(pattern), index(0), root(NULL)
{
	try
	{
		root = parse();
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		exit(0);
	}
}

Regex::~Regex()
{
	delete root;
}

void Regex::printTree()
{
	//root->inOrderPrint();
	root->rowOrderPrint();
}

// 只支持与或*，括号及字母数字
Node* Regex::parse()
{
	index = 0;
	Node* root = parseExpr();
	return root;
	if (index != pattern.size()) 
	{
		throw exception("待匹配串有多余部分");
		return NULL;
	}
	else 
	{
		return root;
	}
}

Node* Regex::parseExpr()
{
	Node* lchild = parseTerm();
	Node* root = lchild;
	while (index < pattern.size() && inExprSet(pattern[index]))
	{
		char token = pattern[index];
		Node* rchild = NULL;
		if (token == '|' || token == '&')
		{
			index++;
			rchild = parseTerm();
			root = new Node(token, lchild, rchild);
			lchild = root;
		}
		else if(isalpha(token) || isdigit(token))
		{
			rchild = parseTerm();
			root = new Node('&', lchild, rchild);
			lchild = root;
		}
		else if (token == '(')
		{
			rchild = parseCharSet();
			root = new Node('&', lchild, rchild);
			lchild = root;
		}
	}
	return root;
}

Node* Regex::parseTerm()
{
	Node* charSet = parseCharSet();
	Node* root = charSet;
	while (index < pattern.size() && inTermSet(pattern[index]))
	{
		char token = pattern[index];
		if (token == '*')
		{
			index++;
			root = new Node('*', charSet);
		}
	}
	return root;
}

Node* Regex::parseCharSet()
{
	char token = pattern[index];
	Node* charSet = NULL;
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
		charSet = new Node(token);
	}
	return charSet;
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
