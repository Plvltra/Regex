#include <iostream>
#include <queue>

#include "Node.h"

using namespace std;

Node::Node(char que)
	: Node(que, NULL, NULL)
{
}

Node::Node(char que, Node* lchild)
	: Node(que, lchild, NULL)
{
}

Node::Node(char que, Node* lchild, Node* rchild)
	: content(que), lchild(lchild), rchild(rchild)
{
}

Node::~Node()
{
	if(this->lchild)
		delete this->lchild;
	if (this->rchild)
		delete this->rchild;
}

inline bool Node::isSymbol()
{
	return this->rchild || this->rchild;
}

inline bool Node::isBinOp()
{
	return this->lchild && this->rchild;
}

inline bool Node::isUnaOp()
{
	return this->lchild && !this->rchild;
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
	queue<Node*> que;
	queue<char> branchQue; // 枝杈
	// 保证push的非NULL
	auto safe_push = [&que](Node* value) {
		if (value)
			que.push(value);
	};
	auto branch_push = [&branchQue](Node* value) {
		if (value) {
			if (value->isBinOp()) {
				branchQue.push('/');
				branchQue.push('\\');
			}
			else if(value->isUnaOp()) {
				branchQue.push('/');
			}
		}
	};

	safe_push(this);
	while (!que.empty())
	{
		int count = que.size();
		while (count--)
		{
			Node* top = que.front();
			que.pop();
			cout << top->content << " ";
			safe_push(top->lchild);
			safe_push(top->rchild);
			branch_push(top);
		}
		cout << endl;

		while (!branchQue.empty())
		{
			cout << branchQue.front() << " ";
			branchQue.pop();
		}
		cout << endl;
	}
}