
#include "DFAMatrix.h"
#include "StatSet.h"

using namespace std;

DFAMatrix::DFAMatrix(StatSetPtr start)
{
	insertRow(start);
	extend();
	// println("矩阵赋值g为空");
}

GraphPtr DFAMatrix::buildGraph()
{
	vector<StatPtr> stats;
	for (int i = 0; i < MAX_ROW; i++)
	{
		StatPtr firstElem = toStat(matrix[i][0]);
		for (int j = 1; j < SIZE; j++)
			LinkManager::link(firstElem, matrix[i][j], (char)j);
		stats.push_back(firstElem);
	}
}

void DFAMatrix::extend()
{
	for (int i = 0; i < MAX_ROW; i++)
		rowExtend(i);
}

inline int DFAMatrix::toID(StatSetPtr set)
{
	return setMap[set];
}

StatPtr DFAMatrix::toStat(StatSetPtr set)
{
	return makeStatPtr(set->isEnd, toID(set));
}

void DFAMatrix::rowExtend(int rowIndex)
{
	Row& row = matrix[rowIndex];
	StatSetPtr src = row[0]; // 第一列
	for (int i = 1; i < SIZE; i++)
	{
		Type content = i;
		StatSetPtr extend = src->nextSet(content);
		row[i] = extend;
		// 若存在添加进map及新行中
		if (extend)
		{
			if (!setMap.count(extend))
			{
				setMap[extend] = ++MAX_ID;
				insertRow(extend);
			}
		}
	}
}

void DFAMatrix::insertRow(StatSetPtr set)
{
	if (set)
	{
		matrix.push_back(Row(set));
		MAX_ROW++;
	}
}

