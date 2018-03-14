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
	// �ڲ���������

private:
	// Attributes
	Status * startStat;
	Status* endStat;
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
	void deleteTree();
};