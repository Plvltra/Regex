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
	char getContent();
	Node* getLchild();
	Node* getRchild();
	void inOrderPrint(); // �������
	void rowOrderPrint(); // �������

private:
	char content;
	Node* lchild;
	Node* rchild;
};
