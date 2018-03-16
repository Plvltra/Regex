
#include "DFAMatrix.h"
#include "LinkManager.h"
#include "StatSet.h"
#include "Graph.h"
#include "DataType.h"

using namespace std;

// Row
Row::Row(StatSetPtr first)
{
	arr[0] = first;
}

StatSetPtr& Row::operator[] (int i)
{
	if (i >= 0 && i < SIZE)
		return arr[i];
	else
		throw std::exception("对行索引非法");
}

Elem* Row::begin() 
{
	return arr; 
}

Elem* Row::end()
{
	return arr + SIZE;
}

// DFAMatrix 
DFAMatrix::DFAMatrix(GraphPtr NFAGraph)
{
	StatPtr NFAstart = NFAGraph->getStart();
	if(!NFAstart)
		throw exception("矩阵赋值g为空");

	StatSetPtr stats = make_shared<StatSet>(NFAstart);
	insertRow(stats);
	extend();
}

StatPtr DFAMatrix::buildDFAGraph()
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
	return start;
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
	StatSetPtr src = matrix[rowIndex][0]; // 第一列
	for (int i = 1; i < SIZE; i++)
	{
		Type content = i;
		StatSetPtr extend = src->nextSet(content);
		matrix[rowIndex][i] = extend;
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

