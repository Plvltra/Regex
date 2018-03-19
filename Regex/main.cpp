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
		int mode = 0;
		if (mode == 0)
		{
			Regex re("a");
			re.match("dabc");
		}
		else if(mode == 1) 
		{
			Regex re("abc|d");
			/*GraphPtr g = makeGraph('a');
			GraphPtr g2 = GraphManager::repeatLink(g);
			g2->printGraph();
			NFAGraphPtr g3 = makeNFAGraph(g2);
			StatPtr s = g3->getStart();
			g3->printGraph();
			DFAGraphPtr g4 = makeDFAGraph(g3);
			g4->printGraph();*/
		}
		cout << "finished" << endl;

		//GraphPtr g1 = makeGraph('a');
		//GraphPtr g2 = makeGraph('b');
		//GraphPtr g3 = makeGraph('c');
		//GraphPtr g5 = GraphManager::bingLink(Graphes{ g1, g2, g3 });

		//GraphPtr g4 = makeGraph('d');
		//GraphPtr g6 = GraphManager::bingLink(Graphes{ g4, g5 });
		////GraphPtr g6 = GraphManager::repeatLink(g4);
		//g6->printGraph();
		//NFAGraphPtr ng = makeNFAGraph(g6);
		//ng->printGraph();
		//DFAGraphPtr dg = makeDFAGraph(ng);
		//dg->printGraph();

		//using Arithmetic::test;
		//test();

		//Regex regex("a(bc*|de*)");
		////Regex regex("a|b|c|d|e|f");
		//regex.printTree();

		/*NodePtr lchild = new Node('a');
		NodePtr rchild = new Node('b');
		NodePtr root = new Node('&', lchild, rchild);
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