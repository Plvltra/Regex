#pragma once

#include "EpsilonNFA.h"
#include "DataType.h"

class Graph
{
public:
	// Constructors & Destructors
	Graph(Status* startStat, Status* endStat);
	// Functions
	Status* getStart() { return startStat; }
	Status* getEnd() { return endStat; }
	void toNFA(); // epsNFA ->NFA
	void toDFA(); // NFA -> DFA
	void printGraph();
	// 内部定义类型

private:
	// Attributes
	Status * startStat;
	Status* endStat;
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
	void deleteTree();
};