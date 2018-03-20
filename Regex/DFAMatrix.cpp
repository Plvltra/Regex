
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

void Row::printRow()
{
	for (int i = 0; i < SIZE; i++)
	{
		if (arr[i])
			arr[i]->printSet();
		else
			cout << "()";
		cout << ", ";
	}
}

StatSetPtr& Row::operator[] (int i)
{
	if (i >= 0 && i < SIZE)
		return arr[i];
	else
		throw std::exception("对行索引非法");
}


// StatSetPtrCmp
bool StatSetPtrCmp::operator()(const StatSetPtr ptr1, const StatSetPtr ptr2) const
{
	return *ptr1 < *ptr2;
}

// DFAMatrix 
DFAMatrix::DFAMatrix(NFAGraphPtr NFAGraph)
{
	StatPtr NFAstart = NFAGraph->getStart();
	if(!NFAstart)
		throw exception("矩阵赋值g为空");

	extend(NFAstart);
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

void DFAMatrix::extend(StatPtr start)
{
	// 初始化第一行
	StatSetPtr stats = make_shared<StatSet>(start);
	insertRow(stats);
	// 生成后面的行
	for (int i = 0; i < MAX_ROW; i++)
	{
		rowExtend(i);
		matrix;
	}
}

inline int DFAMatrix::toID(StatSetPtr set)
{
	if (set == NULL || IDMap[set] == 0)
		return 0;
	return IDMap[set];
}

StatPtr DFAMatrix::toStat(StatSetPtr set)
{
	if (set == NULL)
		return NULL;
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
		// 若存在进行新的行插入
		if (extend)
		{
			if(!statMap.count(extend))
				insertRow(extend);
		}
	}
}

void DFAMatrix::insertRow(StatSetPtr rowFirst)
{
	if (!rowFirst)
		throw exception("rowFirst is NULL");
	MAX_ROW++;
	IDMap[rowFirst] = MAX_ROW;
	statMap[rowFirst] = makeStat(rowFirst->isEnd, MAX_ROW);
	matrix.push_back(Row(rowFirst));
}

void DFAMatrix::printMatrix()
{
	for (auto row : matrix)
	{
		row.printRow();
		cout << endl;
	}
	cout << "-----------------------------" << endl;
}