
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
		if (curr->getEnd())
			ans = i;

		auto nexts = curr->nextStats(text[i]);
		if (nexts.empty())
			break;
		else
			curr = nexts[0]; // dfa nextStats()ÊÇµ¥×´Ì¬
	}
	return ans;
}

