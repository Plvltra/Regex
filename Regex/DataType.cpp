#include "DataType.h"

using namespace std;

// StatusÀà
Status::~Status()
{
	LinkManager::deleteLinks(StatPtr(this), this->nextStats());
	LinkManager::deleteLinks(StatPtr(this), this->preStats());
}

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
		StatPtr thisStat(this);
		if (thisStat == stat)
			return true;
	}
	return false;
}

bool Status::next(StatPtr stat)
{
	if (stat)
		return stat->previous(StatPtr(this));
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

