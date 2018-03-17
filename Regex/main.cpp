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
	try
	{
		StatPtr s1 = makeStat();
		StatPtr e1 = makeStat();
		StatPtr s2 = makeStat();
		StatPtr e2 = makeStat();
		StatPtr s3 = makeStat();
		StatPtr e3 = makeStat();
		LinkManager::link(s1, e1, 'a');
		LinkManager::link(s2, e2, 'b');
		LinkManager::link(s3, e3, 'c');
		GraphPtr g1 = makeGraph(s1, e1);
		GraphPtr g2 = makeGraph(s2, e2);
		GraphPtr g3 = makeGraph(s3, e3);
		GraphPtr g5 = GraphManager::bingLink(Graphes{ g1, g2, g3 });

		StatPtr s4 = makeStat();
		StatPtr e4 = makeStat();
		LinkManager::link(s4, e4, 'd');
		GraphPtr g4 = makeGraph(s4, e4);
		
		GraphPtr g6 = GraphManager::bingLink(Graphes{ g4, g5 });
		//GraphPtr g6 = GraphManager::repeatLink(g4);

		g6->printGraph();
		NFAGraphPtr ng = makeNFAGraph(g6);
		ng->printGraph();
		DFAGraphPtr dg = makeDFAGraph(ng);
		dg->printGraph();
		
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
	catch (...)
	{
		cout << "got exception" << endl;
	}
}