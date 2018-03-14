#include <set>

#include "Graph.h"
using namespace std;

// Graph��
int Graph::MAX_ID = 0;

Graph::Graph(Status* startStat, Status* endStat)
	: startStat(startStat), endStat(endStat)
{
	if (!startStat || !endStat)
		throw std::exception("����ͼ���ڿ�ָ��");
	endStat->setEnd(true);
}

void Graph::toNFA()
{
	markValid();
	eraseInvalid();

	auto deleteEpsEdge = [](Status* stat) {
		for (auto next : stat->nextStats())
		{
			if (LinkManager::getLinkCont(stat, next) == epsilon)
				LinkManager::skipStat(stat, next);
		}
	};
	bfs(deleteEpsEdge);
}

void Graph::toDFA()
{

}

void Graph::bfs(StatDealer dealer)
{
	StatQue sq;
	sq.push(startStat);
	startStat->checked = true;
	while (!sq.empty())
	{
		Status* front = sq.front();
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

void Graph::resetChecked()
{
	StatQue sq;
	sq.push(startStat);
	startStat->checked = false;
	while (!sq.empty())
	{
		Status* front = sq.front();
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

void Graph::markValid()
{
	// �����ȫΪeps����Ϊ��Ч
	auto setValid = [](Status* stat) {
		Edges inEdges = stat->getInEdges();
		bool useful = false;
		for (auto edge : inEdges)
		{
			if (edge->getContent() != epsilon)
				useful = true;
		}

		if (useful)
			stat->valid = true;
		else
			stat->valid = false;
	};
	bfs(setValid);
	startStat->valid = true; // �����׸���Ч
}

void Graph::eraseInvalid()
{
	auto erase = [](Status* stat) {
		if (!stat->valid)
			LinkManager::eraseStat(stat);
	};
	bfs(erase);
	// printGraph(); // debug
}

// ֻ����һ��
void Graph::printGraph()
{
	assignID();
	queue<Status*> que;
	queue<Type> typeQue;

	Status* start = getStart();
	que.push(start);
	while (!que.empty())
	{
		int size = que.size();
		while (size--)
		{
			// ���ID
			Status* front = que.front();
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

void Graph::assignID()
{
	resetID();
	auto assign = [](Status* stat) {
		stat->ID = ++MAX_ID;
	};
	bfs(assign);
}

void Graph::resetID()
{
	auto reset = [](Status* stat) {
		stat->ID = 0;
	};
	bfs(reset);
	MAX_ID = 0;
}

void Graph::deleteTree()
{
	auto deleteStat = [](Status* stat) {
		delete stat;
	};
	bfs(deleteStat);
}
