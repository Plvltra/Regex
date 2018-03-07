#include <iostream>
#include <queue>

#include "Node.h"

using namespace std;

Node::Node(char cont)
	: Node(cont, NULL, NULL)
{
}

Node::Node(char cont, Node* lchild)
	: Node(cont, lchild, NULL)
{
}

Node::Node(char cont, Node* lchild, Node* rchild)
	: content(cont), lchild(lchild), rchild(rchild)
{
}

Node::~Node()
{
	if (this)
	{
		delete this->lchild;
		delete this->rchild;
	}
}

inline bool Node::isSymbol()
{
	return this->rchild || this->rchild;
}

inline char Node::getContent()
{
	return this->content;
}

inline Node* Node::getLchild()
{
	return this->lchild;
}

inline Node* Node::getRchild()
{
	return this->rchild;
}

void Node::inOrderPrint()
{
	if (!this)
		return;

	if (this->lchild)
		lchild->inOrderPrint();
	cout << this->content;
	if (this->rchild)
		rchild->inOrderPrint();
}

void Node::rowOrderPrint()
{
	queue<Node*> cont;
	// 保证push的非NULL
	auto safe_push = [&cont](Node* value) {
		if (value)
			cont.push(value);
	};

	safe_push(this);
	while (!cont.empty())
	{
		int count = cont.size();
		while (count--)
		{
			Node* top = cont.front();
			cont.pop();
			cout << top->content << " ";
			safe_push(top->lchild);
			safe_push(top->rchild);
		}
		cout << endl;
	}
}