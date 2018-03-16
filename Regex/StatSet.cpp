
#include "StatSet.h"
#include "DataType.h"

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

inline void StatSet::insert(StatPtr stat)
{
	elems.insert(stat);
}

bool StatSet::operator== (const StatSet& other) const
{
	return elems == other.elems;
}

StatSetPtr StatSet::nextSet(Type linkCont)
{
	auto nextSet = make_shared<StatSet>();
	for (auto elem : elems)
	{
		for (auto temp : elem->nextStats(linkCont))
			nextSet->insert(temp);
	}
	if (nextSet->empty())
		return NULL;
	else
		return nextSet;
}

auto StatSet::begin()
{
	return elems.begin();
}
auto StatSet::end()
{
	return elems.end();
}
bool StatSet::size()
{
	return elems.size();
}
bool StatSet::empty()
{
	return elems.empty();
}
