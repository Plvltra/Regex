#pragma once

#include <memory>
#include <set>

#include "DataType.h"
#include "EpsilonNFA.h"

class StatSet
{
public:
	// Constructors
	StatSet() = default;
	StatSet(Stats& stats);
	// Functions
	void insert(Status* stat);
	bool operator== (const StatSet& other) const;
	std::shared_ptr<StatSet> nextSet(Type linkCont);
	// Attributes
	bool isEnd;
	std::set<Status*> elems;

private:
};