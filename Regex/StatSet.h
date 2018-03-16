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
	void insert(StatPtr stat);
	bool operator== (const StatSet& other) const;
	/* @func: 返回此状态集进过一步符号变换得到的状态集
	   @return:   返回下一个状态集, NULL对应状态集为空, */
	StatSetPtr nextSet(Type linkCont);
	auto begin() { return elems.begin(); }
	auto end() { return elems.end(); }
	bool size() { return elems.size(); }
	bool empty() { return elems.empty(); }
	// Attributes
	bool isEnd;

private:
	std::set<StatPtr> elems;
};