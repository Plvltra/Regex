#include "DataType.h"

using namespace std;

// Status��
Status::~Status()
{
	/*for (auto inEdge : inEdges)
	delete inEdge;
	for (auto outEdge : outEdges)
	delete outEdge;*/
}

Stats Status::nextStats()
{
	Stats nextStats;
	for (auto edge : outEdges)
		nextStats.push_back(edge->getTo());
	return nextStats;
}

Stats Status::preStats()
{
	Stats preStats;
	for (auto edge : inEdges)
		preStats.push_back(edge->getFrom());
	return preStats;
}

Conts Status::nextContents()
{
	Edges edges = getOutEdges();
	Conts contents;
	for (auto edge : edges)
		contents.push_back(edge->getContent());
	return contents;
}

bool Status::inStats(Stats stats)
{
	for (auto stat : stats)
	{
		if (this == stat)
			return true;
	}
	return false;
}

bool Status::next(Status* stat)
{
	if (stat)
		return stat->previous(this);
	else
		return false;
}

bool Status::previous(Status* stat)
{
	if (stat)
	{
		Stats nexts = this->nextStats();
		return stat->inStats(nexts);
	}
	return false;
}

// Graph��
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

	printGraph();
	cout << "--------------" << endl;

	auto deleteEps = [](Status* stat) {
		StatQue sq;
		for (auto next : stat->nextStats())
			sq.push(next);
		while (!sq.empty())
		{
			Status* front = sq.front();
			sq.pop();
			if (LinkManager::getLinkCont(stat, front) == epsilon)
			{
				for (auto temp : front->nextStats())
					sq.push(temp);
				LinkManager::skipStat(stat, front);
			}
		}
	};
	bfs(deleteEps);
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
}

void Graph::eraseInvalid()
{
	auto erase = [](Status* stat) {
		if (!stat->valid)
			LinkManager::eraseStat(stat);
	};
	bfs(erase);
}

// ֻ����һ��
void Graph::printGraph()
{
	queue<Status*> que;
	queue<Type> typeQue;
	int ID = 0;

	Status* start = getStart();
	start->ID = ++ID;
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
				if (!stat->ID) // �ڵ�δ��ӹ�
					stat->ID = ++ID;
				que.push(stat);
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
}