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
	std::map<StatSetPtr, int> IDMap;
	std::map<StatSetPtr, StatPtr> statMap;
	// Functions
	void extend(StatPtr start); // 扩展整个矩阵 
	int toID(StatSetPtr set); 
	StatPtr toStat(StatSetPtr set); // 返回状态集映射的状态
	void rowExtend(int rowIndex);
	void insertRow(StatSetPtr set);
	void printMatrix();
};
