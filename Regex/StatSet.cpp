
#include "StatSet.h"
#include "DataType.h"

using namespace std;

StatSet::StatSet(StatPtr stat)
{
	this->isEnd = stat->getEnd();
	insert(stat);
}

StatSet::StatSet(Stats& stats)
{
	this->isEnd = false;
	for (auto stat : stats)
	{
		insert(stat);
		if (stat->getEnd())
			this->isEnd = true;
	}
}

bool StatSet::operator== (const StatSet& other) const
{
	return elems == other.elems;
}

StatSetPtr StatSet::nextSet(Type linkCont)
{
	auto nextSet = makeStatSet();
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

inline void StatSet::insert(StatPtr stat)
{
	elems.insert(stat);
	if (stat->getEnd())
		this->isEnd = true;
}
auto StatSet::begin()
{
	return elems.begin();
}
auto StatSet::end()
{
	return elems.end();
}
int StatSet::size()
{
	return elems.size();
}
bool StatSet::empty()
{
	return elems.empty();
}

void StatSet::printSet()
{
	cout << "(";
	int size = this->size();
	for (auto elem: elems)
		cout << elem->ID << " ";
	cout << ")";
}
