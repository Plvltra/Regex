
#include "DFAMatrix.h"
#include "StatSet.h"
#include "DataType.h"

using namespace std;

DFAMatrix::DFAMatrix(StatSetPtr start)
{
	insertRow(start);
	extend();
	// println("矩阵赋值g为空");
}

GraphPtr DFAMatrix::buildGraph()
{
	for (int i = 0; i < MAX_ROW; i++)
	{
		StatPtr firstElem = toStat(matrix[i][0]);
		for (int j = 1; j < SIZE; j++)
		{
			auto nextElem = toStat(matrix[i][j]);
			if(nextElem)
				LinkManager::link(firstElem, nextElem, (char)j);
		}
	}
	StatPtr start = toStat(matrix[0][0]);
	return makeGraphPtr(start);
}

void DFAMatrix::extend()
{
	for (int i = 0; i < MAX_ROW; i++)
		rowExtend(i);
}

inline int DFAMatrix::toID(StatSetPtr set)
{
	if (set == NULL)
		return 0;
	return IDMap[set];
}

StatPtr DFAMatrix::toStat(StatSetPtr set)
{
	if (set == NULL)
		return NULL;
	if (!statMap.count(set))
		statMap[set] = makeStatPtr(set->isEnd, toID(set));
	else
		return statMap[set];
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
			if (!IDMap.count(extend))
			{
				IDMap[extend] = ++MAX_ID;
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

