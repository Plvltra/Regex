#pragma once

#include "EpsilonNFA.h"

class Status : public std::enable_shared_from_this<Status>
{
public:
	int ID; // Debug var
	bool checked;
	bool valid;
	// Constructors & Destructors
	Status();
	Status(bool isEnd, int ID);
	// Functions
	void setEnd(bool isEnd);
	bool getEnd();
	void addInEdge(EdgePtr in);
	void addInEdges(Edges& edges);
	void addOutEdge(EdgePtr out);
	void addOutEdges(Edges& edges);
	Edges& getInEdges();
	Edges& getOutEdges();
	// 获得后继状态
	// @return: 不存在返回空集合
	Stats nextStats();
	// @return: 不存在返回空集合
	Stats nextStats(Type linkCont); // 指定连接内容
	// 获得前驱状态
	Stats preStats();
	// 获得后继边内容
	std::vector<Type> nextContents();
	bool inStats(Stats stats);
	bool next(StatPtr stat, Type content);
	bool previous(StatPtr stat, Type content);

private:
	bool isEnd;
	Edges inEdges;
	Edges outEdges;
};

class StatusEdge
{
public:
	// Constructors & Destructors
	StatusEdge(Type content, StatPtr fromStat, StatPtr toStat);
	virtual ~StatusEdge();
	// Functions
	Type getContent();
	StatPtr getFrom();
	StatPtr getTo();


private:
	Type content;
	StatPtr fromStat;
	StatPtr toStat;
};
