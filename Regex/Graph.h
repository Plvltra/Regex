#pragma once

#include "EpsilonNFA.h"

class BaseGraph
{
public:
	// Constructors & Destructors
	BaseGraph(StatPtr start);
	// Functions
	StatPtr getStart();
	void printGraph();
protected:
	// Attributes
	static int MAX_ID;			 // 初始值为0，对节点范围[1, MAX_ID]
	StatPtr startStat;
	// Functions
	void bfs(StatDealer dealer); // bfs遍历过程中处理数据
	void resetChecked();		 // 若图中所有节点都是检查过的, 则函数可将所有节点置为未检查状态
	void assignID();			 // 分配ID
	void resetID();				 // 重置ID
	
};

class Graph : public BaseGraph
{
public:
	// Constructors & Destructors
	Graph(StatPtr startStat, StatPtr endStat);
	// Functions
	StatPtr getEnd();
	void toNFA();				// epsNFA ->NFA

private:
	// Attributes
	StatPtr endStat;
	// Functions
	void markValid();
	void eraseInvalid();
};