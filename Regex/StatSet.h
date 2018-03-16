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
	/* @func: ���ش�״̬������һ�����ű任�õ���״̬��
	   @return:   ������һ��״̬��, NULL��Ӧ״̬��Ϊ��, */
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