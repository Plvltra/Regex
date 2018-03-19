
#include "Graph.h"
#include "DFAMatrix.h"
#include "DataType.h"

using namespace std;

DFAGraph::DFAGraph(NFAGraphPtr NFAGraph)
{
	matrix = makeMatrix(NFAGraph);
	startStat = matrix->buildDFAGraph();
	assignID();
}

int DFAGraph::match(const string& text)
{
	int size = text.size();
	StatPtr curr = startStat;
	int ans = -1;
	for (int i = 0; i < size; i++)
	{
		// 每接受一个状态，向后扩展
		if (curr->getEnd())
			ans++;

		auto next = nextStat(curr, text[i]);
		if (!next)
			break;
		else
			curr = next; // dfa nextStats()是单状态
	}
	return ans;
}

StatPtr DFAGraph::nextStat(StatPtr stat, Type content)
{
	for (auto edge : stat->getOutEdges())
	{
		if (edge->getContent() == content)
			return edge->getTo();
	}
	return NULL;
}
