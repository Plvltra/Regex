
#include "LinkManager.h"

using namespace std;

// LinkManager
// ��������״̬
void LinkManager::link(Status* from, Status* to, Type content)
{
	if (!from || !to)
		throw exception("����ʧ�ܣ����ڿ�ָ��");

	if (isLinked(from, to))
		return;
	StatusEdge* edge = new StatusEdge(content, from, to);
	from->addOutEdge(edge);
	to->addInEdge(edge);
}

void LinkManager::link(Status* from, Stats& tos, Conts& contents)
{
	if (tos.size() != contents.size())
		throw exception("����ʧ�ܣ����ڿ�ָ��");

	int size = tos.size();
	for (int i = 0; i < size; i++)
		link(from, tos[i], contents[i]);
}

// �ݹ�ɾ��ĳһ״̬��̵�epsilon��
void LinkManager::deleteEps(Status* currStat)
{
	if (!currStat)
		return;
	// �������״̬
	queue<Status*> nextStats;
	// ��δ���ɾ�����Ľڵ����
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
			// ����̽ڵ�Ϊ�յ��ҵ�ǰ�ڵ����ڵ�����ӣ���˽ڵ�ҲΪ�յ�
			if (nextStat->getEnd())
				currStat->setEnd(true);
			auto tagStats = nextStat->nextStats();
			auto tagConts = nextStat->nextContents();
			// ��Ӵ��鿴״̬
			for (auto tagStat : tagStats)
				checked_push(tagStat);
			// ɾ��û�õı�
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