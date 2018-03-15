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
	/* @func: ���ش�״̬������һ�����ű任�õ���״̬��
	   @return:   ������һ��״̬��, NULL��Ӧ״̬��Ϊ��, */
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