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
	StatSetPtr& operator[] (int i); // 返回lvalue
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
	// 返回图的起点
	StatPtr buildDFAGraph();
private:
	// Attributes
	int MAX_ROW = 0; // Row -> [0,MAX_ROW)   ID -> [1,MAX_ID]
	std::vector<Row> matrix;
	std::map<StatSetPtr, int, StatSetPtrCmp> IDMap;
	std::map<StatSetPtr, StatPtr, StatSetPtrCmp> statMap;
	// Functions
	void extend(StatPtr start); // 扩展整个矩阵 
	int toID(StatSetPtr set); 
	StatPtr toStat(StatSetPtr set); // 返回状态集映射的状态
	void rowExtend(int rowIndex);
	void insertRow(StatSetPtr set); // 扩展行，行首与ID，状态一一对应, 所以同时创建增添IDMap, statMap
	void printMatrix();
};
