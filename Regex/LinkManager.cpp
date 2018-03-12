
#include "LinkManager.h"

using namespace std;

// LinkManager
// 连接两个状态
void LinkManager::link(Status* from, Status* to, Type content)
{
	if (!from || !to)
		throw exception("连接失败，存在空指针");

	if (isLinked(from, to))
		return;
	StatusEdge* edge = new StatusEdge(content, from, to);
	from->addOutEdge(edge);
	to->addInEdge(edge);
}

void LinkManager::link(Status* from, Stats& tos, Conts& contents)
{
	if (tos.size() != contents.size())
		throw exception("连接失败，存在空指针");

	int size = tos.size();
	for (int i = 0; i < size; i++)
		link(from, tos[i], contents[i]);
}

// 递归删除某一状态后继的epsilon边
void LinkManager::deleteEps(Status* currStat)
{
	if (!currStat)
		return;
	// 待检查后继状态
	queue<Status*> nextStats;
	// 将未检测删除过的节点放入
	auto checked_push = [&nextStats](Status* stat) {
		if (!stat->checked)
		{
			nextStats.push(stat);
			stat->checked = true;
		}
	};

	for (auto stat : currStat->nextStats())
		checked_push(stat);
	while (!nextStats.empty())
	{
		Status* nextStat = nextStats.front();
		nextStats.pop();
		StatusEdge* link = LinkManager::getLink(currStat, nextStat);
		if (link->getContent() == epsilon)
		{
			// 若后继节点为终点且当前节点与后节点空连接，则此节点也为终点
			if (nextStat->getEnd())
				currStat->setEnd(true);
			auto tagStats = nextStat->nextStats();
			auto tagConts = nextStat->nextContents();
			// 添加待查看状态
			for (auto tagStat : tagStats)
				checked_push(tagStat);
			// 删除没用的边
			LinkManager::link(currStat, tagStats, tagConts);
			LinkManager::deleteLink(currStat, nextStat);
			LinkManager::deleteLink(nextStat, tagStats);
		}
	}
}

bool LinkManager::isLinked(Status* stat, Status* nextStat)
{
	if (stat == NULL || nextStat == NULL)
		return false;
	Stats nextStats = stat->nextStats();
	return nextStat->inStats(nextStats);
}

StatusEdge* LinkManager::getLink(Status* stat, Status* nextStat)
{
	if (stat == NULL)
		return NULL;
	Edges outEdges = stat->getOutEdges();
	for (auto edge : outEdges)
	{
		if (edge->getTo() == nextStat)
			return edge;
	}
	return NULL;
}

void LinkManager::deleteLink(Status* stat, Status* nextStat)
{
	StatusEdge* edge = getLink(stat, nextStat);
	if (edge)
	{
		auto deleteElem = [](Edges& edges, StatusEdge* elem) {
			for (auto itr = edges.begin(); itr != edges.end(); itr++)
			{
				if (*itr == elem)
				{
					edges.erase(itr);
					break;
				}
			}
		};
		Edges& edges = stat->getOutEdges();
		Edges& nextEdges = nextStat->getOutEdges();
		deleteElem(edges, edge);
		deleteElem(nextEdges, edge);
		delete edge; // TODO:
	}
}

void LinkManager::deleteLink(Status* stat, Stats& nextStats)
{
	for (Status* nextStat : nextStats)
		deleteLink(stat, nextStat);
}