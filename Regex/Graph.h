#pragma once

#include "EpsilonNFA.h"
#include "DataType.h"
#include "StatSet.h"
#include "DFAMatrix.h"
#include "Graph.h"

class Graph
{
public:
	// Constructors & Destructors
	Graph(StatPtr start);
	Graph(StatPtr startStat, StatPtr endStat);
	// Functions
	StatPtr getStart() { return startStat; }
	StatPtr getEnd() { return endStat; }
	void toNFA(); // epsNFA ->NFA
	void toDFA(); // NFA -> DFA
	void printGraph();
	// 内部定义类型

private:
	// Attributes
	StatPtr startStat;
	StatPtr endStat;
	static int MAX_ID; // 从1开始
	// Functions
	void bfs(StatDealer dealer); // bfs遍历过程中处理数据
	// 若图中所有节点都是检查过的, 则函数可将所有节点置为未检查状态
	void resetChecked();
	void markValid();
	void eraseInvalid();
	// 重新分配ID
	void assignID();
	void resetID();
};