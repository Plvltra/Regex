
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
			// TODO：加判断
			LinkManager::skipStat(stat, next, epsilon);
		}
	};
	bfs(deleteEpsEdge);
}

void NFAGraph::markValid()
{
	// 进入边全为eps则设为无效
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
	startStat->valid = true; // 设置首个有效
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
