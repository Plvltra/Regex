
#include "Graph.h"
#include "LinkManager.h"
#include "DataType.h"

using namespace std;

NFAGraph::NFAGraph(GraphPtr graph)
{
	startStat = graph->getStart();
	buildNFAGraph();
	assignID();
}

void NFAGraph::buildNFAGraph()
{
	markValid();
	eraseInvalid();

	auto deleteEpsEdge = [](StatPtr stat) {
		for (auto next : stat->nextStats())
		{
			// TODO�����ж�
			LinkManager::skipStat(stat, next, epsilon);
		}
	};
	bfs(deleteEpsEdge);
}

void NFAGraph::markValid()
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

void NFAGraph::eraseInvalid()
{
	auto erase = [](StatPtr stat) {
		if (!stat->valid)
			LinkManager::eraseStat(stat);
	};
	bfs(erase);
	// printGraph(); // debug
}
