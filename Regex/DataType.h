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
	// ��ú��״̬
	Stats nextStats();
	Stats nextStats(Type linkCont); // ָ����������
	// ���ǰ��״̬
	Stats preStats();
	// ��ú�̱�����
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
