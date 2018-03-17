#include <set>

#include "Graph.h"
#include "LinkManager.h"
#include "GraphManager.h"
#include "DataType.h"
#include "StatSet.h"
#include "DFAMatrix.h"

using namespace std;

// Graph类

Graph::Graph(StatPtr start, StatPtr end)
{
	if (!start|| !end)
		throw std::exception("构建图存在空指针");
	startStat = start;
	endStat = end;
	endStat->setEnd(true);
}

StatPtr Graph::getEnd()
{
	return endStat;
}