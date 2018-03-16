#pragma once

#include "EpsilonNFA.h"

class Graph
{
public:
	// Constructors & Destructors
	Graph(StatPtr startStat, StatPtr endStat);
	// Functions
	StatPtr getStart();
	StatPtr getEnd();
	void toNFA(); // epsNFA ->NFA
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