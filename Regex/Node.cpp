#include <iostream>
#include <queue>

#include "Node.h"

using namespace std;

NodePtr makeNode(char cont)
{
	return make_shared<Node>(cont);
}
NodePtr makeNode(char cont, NodePtr lchild)
{
	return make_shared<Node>(cont, lchild);
}
NodePtr makeNode(char cont, NodePtr lchild, NodePtr rchild)
{
	return make_shared<Node>(cont, lchild, rchild);
}

Node::Node(char que)
	: Node(que, NULL, NULL)
{
}

Node::Node(char que, NodePtr lchild)
	: Node(que, lchild, NULL)
{
}

Node::Node(char que, NodePtr lchild, NodePtr rchild)
	: content(que), lchild(lchild), rchild(rchild)
{
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
	queue<NodePtr> que;
	queue<char> branchQue; // 枝杈
	// 保证push的非NULL
	auto safe_push = [&que](NodePtr value) {
		if (value)
			que.push(value);
	};
	auto branch_push = [&branchQue](NodePtr value) {
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

	safe_push(shared_from_this());
	while (!que.empty())
	{
		int count = que.size();
		while (count--)
		{
			NodePtr top = que.front();
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