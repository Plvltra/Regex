
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

// GraphManager
void GraphManager::epsToNFA(Graph* graph)
{
	if (!graph)
		return;

	Status* start = graph->getStart();
	Status* end = graph->getEnd();
	queue<Status*> que;
	que.push(start);
	while (!que.empty())
	{
		// 删除空节点
		Status* currStat = que.front();
		que.pop();
		if (currStat)
			LinkManager::deleteEps(currStat);
		// 添加后继节点
		if (currStat != end)
		{
			auto nextStats = currStat->nextStats();
			for (auto nextStat : nextStats)
				que.push(nextStat);
		}
	}
}

// 只能用一次
void GraphManager::printGraph(Graph* graph)
{
	queue<Status*> que;
	queue<Type> typeQue;
	int ID = 0;

	Status* start = graph->getStart();
	start->ID = ++ID;
	que.push(start);
	while (!que.empty())
	{
		int size = que.size();
		while (size--)
		{
			// 输出ID
			Status* front = que.front();
			que.pop();
			cout << front->ID << boolalpha << front->getEnd() << " ";
			// 添加边内容
			Edges outEdges = front->getOutEdges();
			for (auto edge : outEdges)
				typeQue.push(edge->getContent());
			// 添加下一节点
			Stats nextStats = front->nextStats();
			for (auto stat : nextStats)
			{
				if (!stat->ID) // 节点未入队过
					stat->ID = ++ID;
				que.push(stat);
			}
		}
		cout << endl;

		while (!typeQue.empty())
		{
			cout << typeQue.front() << " ";
			typeQue.pop();
		}
		cout << endl;
	}
}