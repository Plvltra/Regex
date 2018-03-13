#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <string>
#include <regex>
#include <exception>

#include "Arithmetic.h"
#include "Regex.h"
#include "EpsilonNFA.h"
#include "DataType.h"
#include "LinkManager.h"
#include "GraphManager.h"
using namespace std;

class Test
{
	const static int a = 5;
};

int main()
{
	vector<int> v;
	for (auto i : v)
		cout << i << endl;

	Status* s1 = new Status();
	Status* e1 = new Status();
	Status* s2 = new Status();
	Status* e2 = new Status();
	Status* s3 = new Status();
	Status* e3 = new Status();
	LinkManager::link(s1, e1, 'a');
	LinkManager::link(s2, e2, 'b');
	LinkManager::link(s3, e3, 'c');
	Graph* g1 = new Graph(s1, e1);
	Graph* g2 = new Graph(s2, e2);
	Graph* g3 = new Graph(s3, e3);
	Graphes graphes = { g1, g2, g3 };
	Graph* g4 = GraphManager::bingLink(graphes);

	g4->toNFA();
	g4->printGraph();

	//using Arithmetic::test;
	//test();
	
	//Regex regex("a(bc*|de*)");
	////Regex regex("a|b|c|d|e|f");
	//regex.printTree();

	/*Node* lchild = new Node('a');
	Node* rchild = new Node('b');
	Node* root = new Node('&', lchild, rchild);
	root->rowPrint();*/

	//string src = "asduhb@qq.com";
	////string pattern = "([a-z,A-Z,0-9]+)@([a-z,A-Z,0-9]+).([a-z,A-Z,0-9]+)";
	//string pattern = "[a-z][a-z]";
	//regex rgx(pattern);
	//smatch results;
	//regex_search(src, results, rgx);
	//for (auto result : results)
	//	cout << result << endl;
}