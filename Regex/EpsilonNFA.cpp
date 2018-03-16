#include "EpsilonNFA.h"
#include "Graph.h"
#include "DataType.h"
using namespace std;

StatPtr makeStatPtr()
{
	return make_shared<Status>();
}

StatPtr makeStatPtr(bool isEnd, int ID)
{
	return make_shared<Status>(isEnd, ID);
}

GraphPtr makeGraphPtr(StatPtr start)
{
	return make_shared<Graph>(start);
}

GraphPtr makeGraphPtr(StatPtr start, StatPtr end)
{
	return make_shared<Graph>(start, end);
}

EdgePtr makeEdgePtr(Type content, StatPtr fromStat, StatPtr toStat)
{
	return make_shared<StatusEdge>(content, fromStat, toStat);
}