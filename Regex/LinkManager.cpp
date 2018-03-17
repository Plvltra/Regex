
#include "LinkManager.h"
#include "DataType.h"

using namespace std;

void LinkManager::link(StatPtr from, StatPtr to, Type content)
{
	if (!from || !to)
		throw exception("连接失败，存在空指针");
	if (isLinked(from, to))
		return;

	EdgePtr edge = makeEdge(content, from, to);
	from->addOutEdge(edge);
	to->addInEdge(edge);
}

void LinkManager::cross(StatPtr from, StatPtr beCrossed)
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

void LinkManager::skipStat(StatPtr from, StatPtr beSkiped)
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

void LinkManager::eraseStat(StatPtr stat)
{
	if (!stat)
		return;
	debug("Erase Status ID: " + to_string(stat->ID));
	level++;
	// 转换前一节点与此节点的连接
	for (auto preStat : stat->preStats())
	{
		skipStat(preStat, stat);
	}
	deleteLinks(stat, stat->nextStats()); // 删去出的边
	stat.reset();
	level--;
}

bool LinkManager::isLinked(StatPtr stat1, StatPtr stat2)
{
	if (stat1 == NULL || stat2 == NULL)
		return false;
	return stat1->next(stat2) || stat1->previous(stat2);
}

EdgePtr LinkManager::getLink(StatPtr stat1, StatPtr stat2)
{
	// 保持先后顺序
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

Type LinkManager::getLinkCont(StatPtr stat1, StatPtr stat2)
{
	auto edge = getLink(stat1, stat2);
	return edge->getContent();
}

void LinkManager::deleteLink(StatPtr stat1, StatPtr stat2)
{
	// 保持顺序
	EdgePtr edge = getLink(stat1, stat2);
	if (!edge)
		return;
	else if (edge->getFrom() != stat1)
		deleteLink(stat2, stat1);
	debug("Delete Link from: " + to_string(stat1->ID) + " to: " + to_string(stat2->ID));

	// 从容器中删除
	Edges& outEdges = stat1->getOutEdges();
	Edges& inEdges = stat2->getInEdges();
	deleteElem(outEdges, edge);
	deleteElem(inEdges, edge);
}

void LinkManager::deleteLinks(StatPtr stat, Stats& stats)
{
	for (StatPtr stat2 : stats)
		deleteLink(stat, stat2);
}

void LinkManager::deleteElem(Edges& edges, EdgePtr elem) 
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