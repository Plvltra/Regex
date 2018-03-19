
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
		throw std::exception("���������Ƿ�");
}


// DFAMatrix 
DFAMatrix::DFAMatrix(NFAGraphPtr NFAGraph)
{
	StatPtr NFAstart = NFAGraph->getStart();
	if(!NFAstart)
		throw exception("����ֵgΪ��");

	extend(NFAstart);
}

StatPtr DFAMatrix::buildDFAGraph()
{
	matrix;
	StatPtr start1 = toStat(matrix[0][0]);
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
	// ��ʼ����һ��
	StatSetPtr stats = make_shared<StatSet>(start);
	insertRow(stats);
	// ���ɺ������
	for (int i = 0; i < MAX_ROW; i++)
	{
		rowExtend(i);
		matrix;
	}
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
		statMap[set] = makeStat(set->isEnd, toID(set));
	return statMap[set];
}

void DFAMatrix::rowExtend(int rowIndex)
{
	StatSetPtr src = matrix[rowIndex][0]; // ��һ��
	for (int i = 1; i < SIZE; i++)
	{
		Type content = i;
		StatSetPtr extend = src->nextSet(content);
		matrix[rowIndex][i] = extend;
		// �����ڽ����µ��в���
		if (extend)
		{
			// ����Ƿ����extend
			bool exist = false;
			for (auto pair : IDMap)
			{
				StatSetPtr key = pair.first;
				if (*key == *extend)
				{
					exist = true;
					break;
				}
			}
			if(!exist)
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