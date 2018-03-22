
#include "LinkManager.h"
#include "DataType.h"

using namespace std;

void LinkManager::link(StatPtr from, StatPtr to, Type content)
{
	if (!from || !to)
		throw exception("连接失败，存在空指针");

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
	Stats tos = beCrossed->nextStats();
	Conts contents = beCrossed->nextContents();
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

void LinkManager::skipStat(StatPtr from, StatPtr beSkiped, Type content)
{
	if (!from || !beSkiped)
		return;
	debug("Skip Stat from: " + to_string(from->ID) + " beSkiped: " + to_string(beSkiped->ID));
	level++;
	cross(from, beSkiped);
	deleteLink(from, beSkiped, content);
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
		skipStat(preStat, stat);
	deleteLinks(stat, stat->nextStats()); // 删去出的边
	level--;
}

bool LinkManager::isLinked(StatPtr from, StatPtr to)
{
	if (from == NULL || to == NULL)
		return false;
	return from->previous(to) || from->next(to);
}

Edges LinkManager::getLink(StatPtr from, StatPtr to)
{
	if (!from->previous(to))
		return Edges();

	Edges outEdges = from->getOutEdges();
	Edges result;
	for (auto edge : outEdges)
	{
		if (edge->getTo() == to)
			result.push_back(edge);
	}
	return result;
}

Conts LinkManager::getLinkCont(StatPtr from, StatPtr to)
{
	auto edges = getLink(from, to);
	Conts conts;
	for (auto edge : edges)
		conts.push_back(edge->getContent());
	return conts;
}

void LinkManager::deleteLink(StatPtr from, StatPtr to)
{
	// 保持顺序
	Edges edges = getLink(from, to);
	debug("Delete Link from: " + to_string(from->ID) + " to: " + to_string(to->ID));

	// 从容器中删除
	Edges& outEdges = from->getOutEdges();
	Edges& inEdges = to->getInEdges();
	for (auto edge : edges)
	{
		deleteElem(outEdges, edge);
		deleteElem(inEdges, edge);
	}
}

void LinkManager::deleteLink(StatPtr from, StatPtr to, Type content)
{
	// 保持顺序
	Edges edges = getLink(from, to);
	debug("Delete Link from: " + to_string(from->ID) + " to: " + to_string(to->ID));

	// 从容器中删除
	Edges& outEdges = from->getOutEdges();
	Edges& inEdges = to->getInEdges();
	for (auto edge : edges)
	{
		if (edge->getContent() == content)
		{
			deleteElem(outEdges, edge);
			deleteElem(inEdges, edge);
		}
	}
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