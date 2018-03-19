#pragma once
#include <memory>

class Node;
typedef std::shared_ptr<Node> NodePtr;
NodePtr makeNode(char cont);
NodePtr makeNode(char cont, NodePtr lchild);
NodePtr makeNode(char cont, NodePtr lchild, NodePtr rchild);

class Node : public std::enable_shared_from_this<Node>
{
public:
	Node(char cont);
	Node(char cont, NodePtr lchild);
	Node(char cont, NodePtr lchild, NodePtr rchild);

public:
	bool isSymbol();
	bool isBinOp(); // 双目运算符
	bool isUnaOp(); // 单目运算符
	char getContent();
	NodePtr getLchild();
	NodePtr getRchild();
	void inOrderPrint(); // 中序遍历
	void rowOrderPrint(); // 按行输出, / \表示左右枝杈

private:
	char content;
	NodePtr lchild;
	NodePtr rchild;
};

inline bool Node::isSymbol()
{
	return this->lchild || this->rchild;
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

inline NodePtr Node::getLchild()
{
	return this->lchild;
}

inline NodePtr Node::getRchild()
{
	return this->rchild;
}