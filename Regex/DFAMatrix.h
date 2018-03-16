#pragma once

#include <vector>
#include <map>

#include "EpsilonNFA.h"

const int SIZE = 128;
// StatSetPtr Array
typedef StatSetPtr Elem;
struct Row
{
	StatSetPtr arr[SIZE];
	// Functions
	explicit Row(StatSetPtr first);
	StatSetPtr operator[] (int i);
	Elem* begin();
	Elem* end();
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
	// ·µ»Ø×´Ì¬¼¯Ó³ÉäµÄ×´Ì¬
	StatPtr toStat(StatSetPtr set);
	void rowExtend(int rowIndex);
	void insertRow(StatSetPtr set);
};
