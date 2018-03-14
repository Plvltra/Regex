
#include "StatSet.h"

using namespace std;

StatSet::StatSet(Stats& stats)
{
	this->isEnd = false;
	for (auto stat : stats)
	{
		elems.insert(stat);
		if (stat->getEnd())
			this->isEnd = true;
	}
}

inline void StatSet::insert(Status* stat)
{
	elems.insert(stat);
}

bool StatSet::operator== (const StatSet& other) const
{
	return elems == other.elems;
}

shared_ptr<StatSet> StatSet::nextSet(Type linkCont)
{
	auto nextSet = make_shared<StatSet>();
	for (auto elem : elems)
	{
		for (auto temp : elem->nextStats(linkCont))
			nextSet->insert(temp);
	}
	return nextSet;
}
