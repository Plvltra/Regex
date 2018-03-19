#include "DataType.h"
#include "LinkManager.h"

using namespace std;

// StatusÀà
Stats Status::nextStats()
{
	Stats nextStats;
	for (auto edge : outEdges)
		nextStats.push_back(edge->getTo());
	return nextStats;
}

Stats Status::nextStats(Type linkCont)
{
	Stats nextStats;
	for (auto edge : outEdges)
	{
		if (edge->getContent() == linkCont)
			nextStats.push_back(edge->getTo());
	}
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
		if (shared_from_this() == stat)
			return true;
	}
	return false;
}

bool Status::next(StatPtr stat)
{
	if (stat)
		return stat->previous(shared_from_this());
	else
		return false;
}

bool Status::previous(StatPtr stat)
{
	if (stat)
	{
		Stats nexts = this->nextStats();
		return stat->inStats(nexts);
	}
	return false;
}


Status::Status()
	:isEnd(false), ID(0), checked(false), valid(false)
{
}
Status::Status(bool isEnd, int ID)
	: isEnd(isEnd), ID(ID), checked(false), valid(false)
{
}

void Status::setEnd(bool isEnd)
{
	this->isEnd = isEnd;
}
bool Status::getEnd()
{
	return this->isEnd;
}
void Status::addInEdge(EdgePtr in)
{
	inEdges.push_back(in);
}
void Status::addInEdges(Edges& edges)
{
	for (auto edge : edges) addInEdge(edge);
}
void Status::addOutEdge(EdgePtr out)
{
	outEdges.push_back(out);
}
void Status::addOutEdges(Edges& edges)
{
	for (auto edge : edges) addOutEdge(edge);
}
Edges& Status::getInEdges()
{
	return inEdges;
}
Edges& Status::getOutEdges()
{
	return outEdges;
}

// StatusEdge
StatusEdge::StatusEdge(Type content, StatPtr fromStat, StatPtr toStat)
	:content(content), fromStat(fromStat), toStat(toStat)
{
}
StatusEdge::~StatusEdge()
{
}

Type StatusEdge::getContent()
{
	return content;
}
StatPtr StatusEdge::getFrom()
{
	return fromStat;
}
StatPtr StatusEdge::getTo()
{
	return toStat;
}