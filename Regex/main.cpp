#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
using namespace std;

const char epsilon = '\0';

struct Edge;
struct Status;
struct Graph;
struct Edge
{
	char content;
	Status *start;
	Status *end;
	Edge(char content, Status *start, Status *end)
		:content(content), start(start), end(end)
	{
	}
};
struct Status
{
	bool isEnd;
	vector<Edge*> inEdges;
	vector<Edge*> outEdges;
	Status():isEnd(false)
	{
	}
};
struct Graph
{
	Status *start;
	Status *end;
	Graph(Status *start, Status *end)
		: start(start), end(end)
	{
	}
};

Graph link(Status *src, Status *dest, char content)
{
	Edge *edge = new Edge(content, src, dest);
	src->outEdges.push_back(edge);
	dest->inEdges.push_back(edge);
	return Graph(src, dest);
}

Graph chuanLink(Graph src, Graph dest)
{
	Status *end1 = src.end;
	Status *start2 = dest.start;
	end1->isEnd = false;
	link(end1, start2, epsilon);
	return Graph(src.start, dest.end);
}

Graph bingLink(vector<Graph> graphes)
{
	Status *start = new Status();
	Status *end = new Status();
	end->isEnd = true;
	for (auto graph : graphes)
	{
		graph.end->isEnd = false;
		link(start, graph.start, epsilon);
		link(graph.end, end, epsilon);
	}
	return Graph(start, end);
}

//void repeat(Graph graph)
//{
//	Status *status = new Status();
//	Status *end = new Status();
//	end->isEnd = true;
//}

struct Node
{
	char symbol;
	int num;
	Node* lchild;
	Node* rchild;
	Node() = default;
	Node(char symbol, Node* lchild, Node* rchild) 
		: symbol(symbol), lchild(lchild), rchild(rchild){}
	Node(int num) : num(num), lchild(nullptr), rchild(nullptr){}
};

bool isOperator(char c);
Node* parseNum(const string& pattern, int& index);
Node* parseTerm(const string& pattern, int& index);
Node* parseExpr(const string& pattern, int& index);

bool isOperator(char c)
{
	return c == '+' || c == '*';
}

Node* parseNum(const string& pattern, int& index)
{
	string temp;
	while (pattern[index] >= '0' && pattern[index] <= '9')
		temp += pattern[index++];
	// string to num
	int num = atoi(temp.c_str());
	return new Node(num);
}

Node* parseTerm(const string& pattern, int& index)
{

}

Node* parseExpr(const string& pattern, int& index)
{
	Node* num = parseNum(pattern, index);
	while (index < pattern.size() && isOperator(pattern[index]))
	{
		if (pattern[index] == '+')
		{
			index++;
			Node* expr = parseExpr(pattern, index);
			Node* root = new Node('+', num, expr);
			return root;
		}
		else if (pattern[index] == '*')
		{
			index++;
			Node* expr = parseExpr(pattern, index);
			Node* root = new Node('*', num, expr);
			return root;
		}
	}
	return num;
}

int calc(Node* root)
{
	if (!root->lchild && !root->lchild)
	{
		return root->num;
	}
	else
	{
		if (root->symbol == '+')
			return calc(root->lchild) + calc(root->rchild);
		else if(root->symbol == '*')
			return calc(root->lchild) * calc(root->rchild);
	}
}

int main()
{
	int index = 0;
	Node* ans = parseExpr("123*5+32", index);
	cout << calc(ans) << endl;
	//string src = "asduhb@qq.com";
	//string pattern = "([a-z,A-Z,0-9]+)@([a-z,A-Z,0-9]+).([a-z,A-Z,0-9]+)";
	//regex rgx(pattern);
	//smatch results;
	//regex_search(src, results, rgx);
	//for (auto result : results)
	//	cout << result << endl;
}