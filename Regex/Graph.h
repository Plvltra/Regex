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
	static int MAX_ID;			 // ��ʼֵΪ0���Խڵ㷶Χ[1, MAX_ID]
	StatPtr startStat;
	// Functions
	void bfs(StatDealer dealer); // bfs���������д�������
	void resetChecked();		 // ��ͼ�����нڵ㶼�Ǽ�����, �����ɽ����нڵ���Ϊδ���״̬
	void assignID();			 // ����ID
	void resetID();				 // ����ID
	
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