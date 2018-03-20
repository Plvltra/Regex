
#include "Graph.h"
#include "DataType.h"
#include "EpsilonNFA.h"

using namespace std;

int BaseGraph::MAX_ID = 0;

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
		dealer(front); // 最后处理节点，防止处理导致的节点被删除
	}
	resetChecked(); // 复原检查状态
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

// 只能用一次
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
			// 输出ID
			StatPtr front = que.front();
			que.pop();
			cout << front->ID << boolalpha << front->getEnd() << " ";
			// 添加边内容
			Edges outEdges = front->getOutEdges();
			for (auto edge : outEdges)
			{
				typeQue.push(edge->getContent());
				cout << "  " << edge->getContent() << "->";
				auto next = edge->getTo();
				cout << next->ID << boolalpha << next->getEnd() << "  ";
			}
			// 添加下一节点
			Stats nextStats = front->nextStats();
			for (auto stat : nextStats)
			{
				bool repeatPrint = true;
				if (!repeatPrint)
				{
					if (!stat->checked)
					{
						que.push(stat);
						stat->checked = true;
					}
				}
				else
				{
					que.push(stat); // 1: 打印重复的(会造成死循环)
				}
			}
		}
		cout << endl;

		/*while (!typeQue.empty())
		{
			cout << typeQue.front() << " ";
			typeQue.pop();
		}*/
		cout << endl;
	}
	cout << "--------------------" << endl;
	resetChecked();
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