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