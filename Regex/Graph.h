#pragma once

#include "EpsilonNFA.h"

class BaseGraph
{
public:
	// Functions
	StatPtr getStart();
	void printGraph();
protected:
	// Attributes
	static int MAX_ID;		 // TODO: 改变为成员变量 初始值为0，对节点范围[1, MAX_ID]
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
	Graph(Type content);
	Graph(StatPtr startStat, StatPtr endStat);
	// Functions
	StatPtr getEnd();
private:
	// Attributes
	StatPtr endStat;
};

class NFAGraph : public BaseGraph
{
public:
	NFAGraph(GraphPtr graph);
private:
	// Functions
	void buildNFAGraph();			// 通过内部删除边得到NFA图
	void markValid();
	void eraseInvalid();
};

class DFAGraph : public BaseGraph
{
public:
	DFAGraph(NFAGraphPtr NFAGraph);
	// 返回前闭后开
	// return: -1表示不存在匹配
	int match(const std::string& text);
private:
	DFAMatrixPtr matrix;
	// return: stat唯一对应content的状态
	static StatPtr nextStat(StatPtr stat, Type content);
};