#pragma once

class Node
{
public:
	Node(char cont);
	Node(char cont, Node* lchild);
	Node(char cont, Node* lchild, Node* rchild);
	virtual ~Node();

public:
	bool isSymbol();
	bool isBinOp(); // 双目运算符
	bool isUnaOp(); // 单目运算符
	char getContent();
	Node* getLchild();
	Node* getRchild();
	void inOrderPrint(); // 中序遍历
	void rowOrderPrint(); // 按行输出

private:
	char content;
	Node* lchild;
	Node* rchild;
};
