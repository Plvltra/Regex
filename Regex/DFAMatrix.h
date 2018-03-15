#pragma once

#include <vector>
#include <map>

#include "EpsilonNFA.h"
#include "StatSet.h"
#include "Graph.h"
#include "LinkManager.h"

const int SIZE = 128;
// StatSetPtr Array
struct Row
{
	explicit Row(StatSetPtr first) { arr[0] = first; }
	StatSetPtr arr[SIZE];
	StatSetPtr operator[] (int i)
	{
		if (i >= 0 && i < SIZE)
			return arr[i];
		else
			throw std::exception("对行索引非法");
	}
	typedef StatSetPtr Elem;
	Elem* begin() { return arr; }
	Elem* end() { return arr + SIZE; }
};

// DFAMatrix
class DFAMatrix
{
public:
	DFAMatrix(StatSetPtr start);
	GraphPtr buildGraph();
private:
	// Attributes
	int MAX_ID = 0; // ID -> [1,MAX_ID]
	int MAX_ROW = 0; // Row -> [0,MAX_ROW)
	std::vector<Row> matrix;
	std::map<StatSetPtr, int> IDMap;
	std::map<StatSetPtr, StatPtr> statMap;
	// Functions
	void extend();
	int toID(StatSetPtr set);
	// 返回状态集映射的状态
	StatPtr toStat(StatSetPtr set);
	void rowExtend(int rowIndex);
	void insertRow(StatSetPtr set);
};
