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
	static int MAX_ID;		 // TODO: �ı�Ϊ��Ա���� ��ʼֵΪ0���Խڵ㷶Χ[1, MAX_ID]
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
	void buildNFAGraph();			// ͨ���ڲ�ɾ���ߵõ�NFAͼ
	void markValid();
	void eraseInvalid();
};

class DFAGraph : public BaseGraph
{
public:
	DFAGraph(NFAGraphPtr NFAGraph);
	// ����ǰ�պ�
	// return: -1��ʾ������ƥ��
	int match(const std::string& text);
private:
	DFAMatrixPtr matrix;
	// return: statΨһ��Ӧcontent��״̬
	static StatPtr nextStat(StatPtr stat, Type content);
};