#include <set>

#include "Graph.h"
#include "LinkManager.h"
#include "GraphManager.h"
#include "DataType.h"
#include "StatSet.h"
#include "DFAMatrix.h"

using namespace std;

// Graph��

Graph::Graph(StatPtr start, StatPtr end)
{
	if (!start|| !end)
		throw std::exception("����ͼ���ڿ�ָ��");
	startStat = start;
	endStat = end;
	endStat->setEnd(true);
}

StatPtr Graph::getEnd()
{
	return endStat;
}