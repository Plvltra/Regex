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
	// �ڲ���������

private:
	// Attributes
	StatPtr startStat;
	StatPtr endStat;
	static int MAX_ID; // ��1��ʼ
	// Functions
	void bfs(StatDealer dealer); // bfs���������д�������
	// ��ͼ�����нڵ㶼�Ǽ�����, �����ɽ����нڵ���Ϊδ���״̬
	void resetChecked();
	void markValid();
	void eraseInvalid();
	// ���·���ID
	void assignID();
	void resetID();
};