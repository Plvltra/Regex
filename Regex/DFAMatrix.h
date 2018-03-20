#pragma once

#include <vector>
#include <map>

#include "EpsilonNFA.h"

const int SIZE = 128;
// StatSetPtr Array
struct Row
{
	StatSetPtr arr[SIZE];
	// Functions
	void printRow();
	explicit Row(StatSetPtr first);
	StatSetPtr& operator[] (int i); // ����lvalue
};
// StatSetPtr cmp
struct StatSetPtrCmp
{
	bool operator()(const StatSetPtr ptr1, const StatSetPtr ptr2) const;
};

// DFAMatrix
class DFAMatrix
{
public:
	DFAMatrix(NFAGraphPtr NFAGraph);
	// ����ͼ�����
	StatPtr buildDFAGraph();
private:
	// Attributes
	int MAX_ROW = 0; // Row -> [0,MAX_ROW)   ID -> [1,MAX_ID]
	std::vector<Row> matrix;
	std::map<StatSetPtr, int, StatSetPtrCmp> IDMap;
	std::map<StatSetPtr, StatPtr, StatSetPtrCmp> statMap;
	// Functions
	void extend(StatPtr start); // ��չ�������� 
	int toID(StatSetPtr set); 
	StatPtr toStat(StatSetPtr set); // ����״̬��ӳ���״̬
	void rowExtend(int rowIndex);
	void insertRow(StatSetPtr set); // ��չ�У�������ID��״̬һһ��Ӧ, ����ͬʱ��������IDMap, statMap
	void printMatrix();
};
