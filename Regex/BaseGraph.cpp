
#include "Graph.h"
#include "DataType.h"
#include "EpsilonNFA.h"

using namespace std;

BaseGraph::BaseGraph(StatPtr start)
	:startStat(start)
{
	if (!start)
		throw std::exception("����ͼ���ڿ�ָ��");
}

StatPtr BaseGraph::getStart()
{
	return startStat;
}

void BaseGraph::bfs(StatDealer dealer)
{
	StatQue sq;
	sq.push(startStat);
	startStat->checked = true;
	while (!sq.empty())
	{
		StatPtr front = sq.front();
		sq.pop();
		// Add next stats
		Stats nextStats = front->nextStats();
		for (auto stat : nextStats)
		{
			if (!stat->checked)
			{
				sq.push(stat);
				stat->checked = true;
			}
		}
		dealer(front); // �����ڵ㣬��ֹ�����µĽڵ㱻ɾ��
	}
	resetChecked(); // ��ԭ���״̬
}

void BaseGraph::resetChecked()
{
	StatQue sq;
	sq.push(startStat);
	startStat->checked = false;
	while (!sq.empty())
	{
		StatPtr front = sq.front();
		sq.pop();
		// Add next stats
		Stats nextStats = front->nextStats();
		for (auto stat : nextStats)
		{
			if (stat->checked)
			{
				sq.push(stat);
				stat->checked = false;
			}
		}
	}
}

// ֻ����һ��
void BaseGraph::printGraph()
{
	resetID();
	assignID();

	queue<StatPtr> que;
	queue<Type> typeQue;
	StatPtr start = getStart();
	que.push(start);
	while (!que.empty())
	{
		int size = que.size();
		while (size--)
		{
			// ���ID
			StatPtr front = que.front();
			que.pop();
			cout << front->ID << boolalpha << front->getEnd() << " ";
			// ��ӱ�����
			Edges outEdges = front->getOutEdges();
			for (auto edge : outEdges)
				typeQue.push(edge->getContent());
			// �����һ�ڵ�
			Stats nextStats = front->nextStats();
			for (auto stat : nextStats)
			{
				que.push(stat); // 1: ��ӡ�ظ���(�������ѭ��)
			}
		}
		cout << endl;

		while (!typeQue.empty())
		{
			cout << typeQue.front() << " ";
			typeQue.pop();
		}
		cout << endl;
	}
	cout << "--------------------" << endl;
}

void BaseGraph::assignID()
{
	resetID();
	auto assign = [](StatPtr stat) {
		stat->ID = ++MAX_ID;
	};
	bfs(assign);
}

void BaseGraph::resetID()
{
	auto reset = [](StatPtr stat) {
		stat->ID = 0;
	};
	bfs(reset);
	MAX_ID = 0;
}