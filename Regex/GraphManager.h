#pragma once

#include "EpsilonNFA.h"
#include "DataType.h"
#include "LinkManager.h"
#include "Graph.h"

class GraphManager
{
public:
	// ����
	static Graph* chuanLink(Graph* from, Graph* to);
	// ����
	static Graph* bingLink(Graphes& graphes);
	// �ظ� TODO: Debug
	static Graph* repeatLink(Graph* graph);

private:

};

