
#include "GraphManager.h"

using namespace std;

// 串联
Graph* GraphManager::chuanLink(Graph* from, Graph* to)
{
	Status* end1 = from->getEnd(); // from图的结束
	Status* start2 = to->getStart(); // end图的开始
	end1->setEnd(false);
	LinkManager::link(end1, start2, epsilon);
	return new Graph(from->getStart(), to->getEnd());
}
// 并联
Graph* GraphManager::bingLink(Graphes& graphes)
{
	Status* newStart = new Status();
	Status* newEnd = new Status();
	newEnd->setEnd(true);
	for (auto graph : graphes)
	{
		graph->getEnd()->setEnd(false);
		LinkManager::link(newStart, graph->getStart(), epsilon);
		LinkManager::link(graph->getEnd(), newEnd, epsilon);
	}
	return new Graph(newStart, newEnd);
}
// 重复
Graph* GraphManager::repeatLink(Graph* graph)
{
	Status* start = graph->getStart();
	Status* end = graph->getEnd();
	Status* newStart = new Status();
	Status* newEnd = new Status();
	LinkManager::link(newStart, start, epsilon);
	LinkManager::link(end, newEnd, epsilon);
	LinkManager::link(newStart, newEnd, epsilon);
	LinkManager::link(end, start, epsilon);

	end->setEnd(false);
	newEnd->setEnd(true);
	return new Graph(newStart, newEnd);
}
