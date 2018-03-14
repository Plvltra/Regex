
#include "LinkManager.h"

using namespace std;

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

void LinkManager::cross(Status* from, Status* beCrossed)
{
	if (!from || !beCrossed)
		return;
	debug("Cross Link from: " + to_string(from->ID) + " beCrossed: " + to_string(beCrossed->ID));
	level++;
	Stats& tos = beCrossed->nextStats();
	Conts& contents = beCrossed->nextContents();
	int size = tos.size();
	for (int i = 0; i < size; i++)
		link(from, tos[i], contents[i]);
	level--;
}

void LinkManager::skipStat(Status* from, Status* beSkiped)
{
	if (!from || !beSkiped)
		return;
	debug("Skip Stat from: " + to_string(from->ID) + " beSkiped: " + to_string(beSkiped->ID));
	level++;
	cross(from, beSkiped);
	deleteLink(from, beSkiped);
	if (beSkiped->getEnd())
		from->setEnd(true);
	level--;
}

void LinkManager::eraseStat(Status* stat)
{
	if (!stat)
		return;
	debug("Erase Status ID: " + to_string(stat->ID));
	level++;
	// ת��ǰһ�ڵ���˽ڵ������
	for (auto preStat : stat->preStats())
	{
		skipStat(preStat, stat);
	}
	deleteLinks(stat, stat->nextStats()); // ɾȥ���ı�
	delete(stat);
	level--;
}

bool LinkManager::isLinked(Status* stat1, Status* stat2)
{
	if (stat1 == NULL || stat2 == NULL)
		return false;
	return stat1->next(stat2) || stat1->previous(stat2);
}

StatusEdge* LinkManager::getLink(Status* stat1, Status* stat2)
{
	// �����Ⱥ�˳��
	if (!isLinked(stat1, stat2))
		return NULL;
	else if (stat1->next(stat2))
		getLink(stat2, stat1);

	Edges outEdges = stat1->getOutEdges();
	for (auto edge : outEdges)
	{
		if (edge->getTo() == stat2)
			return edge;
	}
}

Type LinkManager::getLinkCont(Status* stat1, Status* stat2)
{
	auto edge = getLink(stat1, stat2);
	return edge->getContent();
}

void LinkManager::deleteLink(Status* stat1, Status* stat2)
{
	// ����˳��
	StatusEdge* edge = getLink(stat1, stat2);
	if (!edge)
		return;
	else if (edge->getFrom() != stat1)
		deleteLink(stat2, stat1);
	debug("Delete Link from: " + to_string(stat1->ID) + " to: " + to_string(stat2->ID));

	// ��������ɾ��
	Edges& outEdges = stat1->getOutEdges();
	Edges& inEdges = stat2->getInEdges();
	deleteElem(outEdges, edge);
	deleteElem(inEdges, edge);
	delete edge; 
}

void LinkManager::deleteLinks(Status* stat, Stats& stats)
{
	for (Status* stat2 : stats)
		deleteLink(stat, stat2);
}

void LinkManager::deleteElem(Edges& edges, StatusEdge* elem) 
{
	for (auto itr = edges.begin(); itr != edges.end(); itr++)
	{
		if (*itr == elem)
		{
			edges.erase(itr);
			return;
		}
	}
}

//---------------------- Debug ----------------------//
int LinkManager::level = 0;

void LinkManager::tab(int n)
{
	while (n--)
		print("    ");
}

void LinkManager::debug(string s)
{
	tab(level);
	println(s);
}