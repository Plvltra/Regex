#include "EpsilonNFA.h"
#include "Graph.h"
#include "DataType.h"
#include "DFAGraph.h"
#include "StatSet.h"
using namespace std;

StatPtr makeStatPtr()
{
	return make_shared<Status>();
}

StatPtr makeStatPtr(bool isEnd, int ID)
{
	return make_shared<Status>(isEnd, ID);
}

DFAGraphPtr makeDFAGraphPtr(GraphPtr graph)
{
	return make_shared<DFAGraph>(graph);
}

GraphPtr makeGraphPtr(StatPtr start, StatPtr end)
{
	return make_shared<Graph>(start, end);
}

EdgePtr makeEdgePtr(Type content, StatPtr fromStat, StatPtr toStat)
{
	return make_shared<StatusEdge>(content, fromStat, toStat);
}

StatSetPtr makeStatSetPtr(StatPtr stat)
{
	return make_shared<StatSet>(stat);
}
