
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
	if (curr->getEnd()) ans = 0;
	for (int i = 0; i < size; i++)
	{
		curr = nextStat(curr, text[i]);
		if (!curr)
			break;
		else if (curr->getEnd()) // 每接受一个状态，向后扩展
			ans = i+1;
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
