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
#include "Graph.h"
using namespace std;

int main()
{
	StatPtr s1 = makeStatPtr();
	StatPtr e1 = makeStatPtr();
	StatPtr s2 = makeStatPtr();
	StatPtr e2 = makeStatPtr();
	StatPtr s3 = makeStatPtr();
	StatPtr e3 = makeStatPtr();
	LinkManager::link(s1, e1, 'a');
	LinkManager::link(s2, e2, 'b');
	LinkManager::link(s3, e3, 'c');
	GraphPtr g1 = makeGraphPtr(s1, e1);
	GraphPtr g2 = makeGraphPtr(s2, e2);
	GraphPtr g3 = makeGraphPtr(s3, e3);
	Graphes graphes = { g1, g2, g3 };
	GraphPtr g4 = GraphManager::bingLink(graphes);

	StatPtr s4 = makeStatPtr();
	StatPtr e4 = makeStatPtr();
	LinkManager::link(s4, e4, 'd');
	GraphPtr g5 = makeGraphPtr(s4, e4);
	
	GraphPtr g6 = GraphManager::chuanLink(g4, g5);
	//GraphPtr g6 = GraphManager::repeatLink(g4);
	g6->printGraph();
	g6->toNFA();
	g6->printGraph();

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