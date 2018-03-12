#include "DataType.h"

using namespace std;

// Status类
Status::~Status()
{
	/*for (auto inEdge : inEdges)
	delete inEdge;
	for (auto outEdge : outEdges)
	delete outEdge;*/
}

Stats Status::nextStats()
{
	Stats nextStats;
	for (auto edge : outEdges)
		nextStats.push_back(edge->getTo());
	return nextStats;
}

Stats Status::preStats()
{
	Stats preStats;
	for (auto edge : inEdges)
		preStats.push_back(edge->getFrom());
	return preStats;
}

Conts Status::nextContents()
{
	Edges edges = getOutEdges();
	Conts contents;
	for (auto edge : edges)
		contents.push_back(edge->getContent());
	return contents;
}

bool Status::inStats(Stats stats)
{
	for (auto stat : stats)
	{
		if (this == stat)
			return true;
	}
	return false;
}

// Graph类
Graph::Graph(Status* startStat, Status* endStat)
	: startStat(startStat), endStat(endStat)
{
	if (!startStat || !endStat)
		throw std::exception("构建图存在空指针");
	endStat->setEnd(true);
	markValid();
}

void Graph::toNFA()
{
	auto deleteEps = [](Status* stat) {
		if(stat)
	};
	bfs(deleteEps);
}

void Graph::bfs(StatDealer dealer)
{
	StatQue sq;
	sq.push(startStat);
	startStat->checked = true;
	while (!sq.empty())
	{
		Status* front = sq.front();
		sq.pop();
		dealer(front);
		// Add next stats
		Stats nextStats = front->nextStats();
		for (auto stat : nextStats)
		{
			if (!stat->checked)
			{
				sq.push(stat);
				stat->checked = true;
			}
		}
	}
	resetChecked(); // 复原
}

void Graph::resetChecked()
{
	StatQue sq;
	sq.push(startStat);
	startStat->checked = false;
	while (!sq.empty())
	{
		Status* front = sq.front();
		sq.pop();
		// Add next stats
		Stats nextStats = front->nextStats();
		for (auto stat : nextStats)
		{
			if (stat->checked)
			{
				sq.push(stat);
				stat->checked = false;
			}
		}
	}
}

void Graph::markValid()
{
	// 进入边全为eps则设为无效
	auto setValid = [](Status* stat) {
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
}