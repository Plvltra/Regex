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
	Status(bool isEnd, int ID) :isEnd(isEnd), ID(ID), checked(false), valid(false) {}
	virtual ~Status();
	// Functions
	void setEnd(bool isEnd) { this->isEnd = isEnd; }
	bool getEnd() { return this->isEnd; }
	void addInEdge(EdgePtr in) { inEdges.push_back(in); }
	void addInEdges(Edges& edges) {
		for (auto edge : edges) addInEdge(edge);
	}
	void addOutEdge(EdgePtr out) { outEdges.push_back(out); }
	void addOutEdges(Edges& edges) {
		for (auto edge : edges) addOutEdge(edge);
	}
	Edges& getInEdges() { return inEdges; }
	Edges& getOutEdges() { return outEdges; }
	// 获得后继状态
	Stats nextStats();
	Stats nextStats(Type linkCont); // 指定连接内容
	// 获得前驱状态
	Stats preStats();
	// 获得后继边内容
	std::vector<Type> nextContents();
	bool inStats(Stats stats);
	bool next(StatPtr stat);
	bool previous(StatPtr stat);

private:
	bool isEnd;
	Edges inEdges;
	Edges outEdges;
};

class StatusEdge
{
public:
	// Constructors & Destructors
	StatusEdge(Type content, StatPtr fromStat, StatPtr toStat)
		:content(content), fromStat(fromStat), toStat(toStat)
	{
	}
	virtual ~StatusEdge() {}
	// Functions
	Type getContent() { return content; }
	StatPtr getFrom() { return fromStat; }
	StatPtr getTo() { return toStat; }


private:
	Type content;
	StatPtr fromStat;
	StatPtr toStat;
};
