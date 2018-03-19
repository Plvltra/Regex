#include "EpsilonNFA.h"
#include "Graph.h"
#include "DataType.h"
#include "StatSet.h"
#include "DFAMatrix.h"
using namespace std;

StatPtr makeStat()
{
	return make_shared<Status>();
}

StatPtr makeStat(bool isEnd, int ID)
{
	return make_shared<Status>(isEnd, ID);
}

NFAGraphPtr makeNFAGraph(GraphPtr graph)
{
	return make_shared<NFAGraph>(graph);
}

DFAGraphPtr makeDFAGraph(NFAGraphPtr NFAGraph)
{
	return make_shared<DFAGraph>(NFAGraph);
}

DFAMatrixPtr makeMatrix(NFAGraphPtr NFAGraph)
{
	return make_shared<DFAMatrix>(NFAGraph);
}

GraphPtr makeGraph(Type content)
{
	return make_shared<Graph>(content);
}

GraphPtr makeGraph(StatPtr start, StatPtr end)
{
	return make_shared<Graph>(start, end);
}

EdgePtr makeEdge(Type content, StatPtr fromStat, StatPtr toStat)
{
	return make_shared<StatusEdge>(content, fromStat, toStat);
}

StatSetPtr makeStatSet()
{
	return make_shared<StatSet>();
}

StatSetPtr makeStatSet(StatPtr stat)
{
	return make_shared<StatSet>(stat);
}
