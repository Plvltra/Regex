#pragma once

#include "EpsilonNFA.h"
#include "LinkManager.h"

class Status
{
public:
	int ID; // Debug var
	bool checked;
	bool valid;
	// Constructors & Destructors
	Status() :isEnd(false), ID(0), checked(false), valid(false) {}
	virtual ~Status();
	// Functions
	void setEnd(bool isEnd) { this->isEnd = isEnd; }
	bool getEnd() { return this->isEnd; }
	void addInEdge(StatusEdge* in) { inEdges.push_back(in); }
	void addInEdges(Edges& edges) {
		for (auto edge : edges) addInEdge(edge);
	}
	void addOutEdge(StatusEdge* out) { outEdges.push_back(out); }
	void addOutEdges(Edges& edges) {
		for (auto edge : edges) addOutEdge(edge);
	}
	Edges& getInEdges() { return inEdges; }
	Edges& getOutEdges() { return outEdges; }
	// 获得后继状态
	Stats nextStats();
	// 获得前驱状态
	Stats preStats();
	// 获得后继边内容
	std::vector<Type> nextContents();
	bool inStats(Stats stats);
	bool next(Status* stat);
	bool previous(Status* stat);

private:
	bool isEnd;
	Edges inEdges;
	Edges outEdges;
};

class StatusEdge
{
public:
	// Constructors & Destructors
	StatusEdge(Type content, Status* fromStat, Status* toStat)
		:content(content), fromStat(fromStat), toStat(toStat)
	{
	}
	virtual ~StatusEdge() {}
	// Functions
	Type getContent() { return content; }
	Status* getFrom() { return fromStat; }
	Status* getTo() { return toStat; }


private:
	Type content;
	Status* fromStat;
	Status* toStat;
};

class Graph
{
public:
	// Constructors & Destructors
	Graph(Status* startStat, Status* endStat);
	// Functions
	Status* getStart() { return startStat; }
	Status* getEnd() { return endStat; }
	void toNFA();

private:
	Status* startStat;
	Status* endStat;
	// bfs遍历过程中处理数据
	void bfs(StatDealer dealer);
	// 若图中所有节点都是检查过的, 则函数可将所有节点置为未检查状态
	void resetChecked();
	void markValid();
	void eraseInvalid();

};