#include <iostream>
#include <cstdlib>

#include "Arithmetic.h"
using namespace std;

/*
 * Expr -> Expr + Term
 *      |  Expr - Term
 *		|  Term
 * Term -> Term * Num
 *		|  Term / Num
 *		|  Num
 * Num  -> (Expr)
 *		|  num
 */
namespace Arithmetic
{
	inline bool isTermOp(char c)
	{
		return c == '*' || c == '/';
	}

	inline bool isExprOp(char c)
	{
		return c == '+' || c == '-';
	}

	inline string quoted(string s)
	{
		return "\'" + s + "\'";
	}

	inline string quoted(char c)
	{
		string s = "\'";
		return s + c + "\'";
	}

	void error(const string& src, int index, string want, string got)
	{
		cout << "Compiler error in expression :  " << endl;
		cout << src << endl;
		// �������λ��
		int space = index;
		while (space--)
			cout << " ";
		cout << '^' << endl;
		// ���������Ϣ
		cout << "Syntax error in position " << index << endl;
		cout << "\texpecting:  " + want << endl;
		cout << "\tbut got  :  " + got << endl;
	}

	// ƥ���pattern[index]��ĵ�һ��Num
	Node* parseNum(const string& pattern, int& index)
	{
		if (index >= pattern.size())
			return NULL;

		string temp;
		if (isdigit(pattern[index]))
		{
			while (isdigit(pattern[index]))
				temp += pattern[index++];
			// string to num
			int num = atoi(temp.c_str());
			return new Node(num);
		}
		if (pattern[index] == '(')
		{
			index++;
			Node* num = parseExpr(pattern, index);
			if (pattern[index] == ')')
			{
				index++;
				return num;
			}
			error(pattern, index, quoted(")"), quoted(pattern[index]));
		}
		error(pattern, index, quoted("0-9") + "or" + quoted("("), quoted(pattern[index]));
	}

	// ƥ���pattern[index]��ĵ�һ��Term
	Node* parseTerm(const string& pattern, int& index)
	{
		if (index >= pattern.size())
			return NULL;

		Node* num = parseNum(pattern, index);
		Node* root = num;
		while (index < pattern.size() && isTermOp(pattern[index]))
		{
			char symbol = pattern[index++];
			// ����
			Node* other_num = parseNum(pattern, index);
			Node* root = new Node(symbol, num, other_num);
			num = root;
		}
		return num;
	}

	Node* parseExpr(const string& pattern, int& index)
	{
		if (index >= pattern.size())
			return NULL;

		Node* term = parseTerm(pattern, index);
		Node* root = term;
		while (index < pattern.size() && isExprOp(pattern[index]))
		{
			char symbol = pattern[index++];
			// ����
			Node* other_term = parseTerm(pattern, index);
			root = new Node(symbol, term, other_term);
			term = root;
		}
		return root;
	}

	Node* parseArithm(const string& pattern)
	{
		int index = 0;
		Node* ans = parseExpr(pattern, index);
		if (index < pattern.size())
		{
			error(pattern, index, quoted("\\0"), quoted(pattern[index]));
			return NULL;
		}
		else
		{
			return ans;
		}
	}

	Node* calc(Node* root)
	{
		if (!root)
			return NULL;

		// root is a number
		if (!(root->lchild) && !(root->lchild))
			return root;
		// ���Һ���ֻ����һ��
		else if (!(root->lchild && root->rchild))
			return NULL;

		int lsum = calc(root->lchild)->num;
		int rsum = calc(root->rchild)->num;
		if (root->symbol == '+')
			return new Node(lsum + rsum);
		else if (root->symbol == '-')
			return new Node(lsum - rsum);
		else if (root->symbol == '*')
			return new Node(lsum * rsum);
		else if (root->symbol == '/')
			return new Node(lsum / rsum);
	}

	// ���ʽ֧���������㼰���ţ���֧�ֿո�
	void test()
	{
		Node* ans = parseArithm("(1-5)/2");
		if (!ans)
			cout << "Calculation error!" << endl;
		else
			cout << calc(ans)->num << endl;
	}
}
