#pragma once

#include <memory>
#include <set>

#include "EpsilonNFA.h"

class StatSet
{
public:
	// Constructors
	StatSet() = default;
	StatSet(StatPtr stat);
	StatSet(Stats& stats);
	// Functions
	void insert(StatPtr stat);
	bool operator== (const StatSet& other) const;
	/* @func: 返回此状态集进过一步符号变换得到的状态集
	   @return:   返回下一个状态集, NULL对应状态集为空, */
	StatSetPtr nextSet(Type linkCont);
	auto begin();
	auto end();
	bool size();
	bool empty();
	// Attributes
	bool isEnd;

private:
	std::set<StatPtr> elems;
};