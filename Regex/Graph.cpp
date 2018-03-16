#include <set>

#include "Graph.h"
#include "LinkManager.h"
#include "GraphManager.h"
#include "DataType.h"
#include "StatSet.h"
#include "DFAMatrix.h"

using namespace std;

// Graph��
int Graph::MAX_ID = 0;

// TODO: debug
Graph::Graph(StatPtr start, StatPtr end)
	: BaseGraph(start), endStat(end)
{
	if (!end)
		throw std::exception("����ͼ���ڿ�ָ��");
	endStat->setEnd(true);
}

StatPtr Graph::getEnd()
{
	return endStat;
}

void Graph::toNFA()
{
	markValid();
	eraseInvalid();

	auto deleteEpsEdge = [](StatPtr stat) {
		for (auto next : stat->nextStats())
		{
			if (LinkManager::getLinkCont(stat, next) == epsilon)
				LinkManager::skipStat(stat, next);
		}
	};
	bfs(deleteEpsEdge);
}

void Graph::markValid()
{
	// �����ȫΪeps����Ϊ��Ч
	auto setValid = [](StatPtr stat) {
		Edges inEdges = stat->getInEdges();
		bool useful = false;
		for (auto edge : inEdges)
		{
			if (edge->getContent() != epsilon)
				useful = true;
		}

		if (useful)
			stat->valid = true;
		else
			stat->valid = false;
	};
	bfs(setValid);
	startStat->valid = true; // �����׸���Ч
}

void Graph::eraseInvalid()
{
	auto erase = [](StatPtr stat) {
		if (!stat->valid)
			LinkManager::eraseStat(stat);
	};
	bfs(erase);
	// printGraph(); // debug
}
