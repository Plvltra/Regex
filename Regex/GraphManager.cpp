
#include "GraphManager.h"
#include "LinkManager.h"
#include "Graph.h"
#include "DataType.h"
#include "StatSet.h"
#include "DFAMatrix.h"

using namespace std;

// 串联
GraphPtr GraphManager::chuanLink(GraphPtr from, GraphPtr to)
{
	StatPtr end1 = from->getEnd(); // from图的结束
	StatPtr start2 = to->getStart(); // end图的开始
	end1->setEnd(false);
	LinkManager::link(end1, start2, epsilon);
	return makeGraph(from->getStart(), to->getEnd());
}
// 并联
GraphPtr GraphManager::bingLink(Graphes graphes)
{
	StatPtr newStart = makeStat();
	StatPtr newEnd = makeStat();
	newEnd->setEnd(true);
	for (auto graph : graphes)
	{
		graph->getEnd()->setEnd(false);
		LinkManager::link(newStart, graph->getStart(), epsilon);
		LinkManager::link(graph->getEnd(), newEnd, epsilon);
	}
	return makeGraph(newStart, newEnd);
}
// 重复
GraphPtr GraphManager::repeatLink(GraphPtr graph)
{
	StatPtr start = graph->getStart();
	StatPtr end = graph->getEnd();
	StatPtr newStart = makeStat();
	StatPtr newEnd = makeStat();
	LinkManager::link(newStart, start, epsilon);
	LinkManager::link(end, newEnd, epsilon);
	LinkManager::link(newStart, newEnd, epsilon);
	LinkManager::link(end, start, epsilon);

	end->setEnd(false);
	newEnd->setEnd(true);
	return makeGraph(newStart, newEnd);
}