#pragma once

#include "EpsilonNFA.h"
#include "DataType.h"
#include "LinkManager.h"

class GraphManager
{
public:
	static void epsToNFA(Graph* graph);
	static void printGraph(Graph* graph);
	// ����
	static Graph* chuanLink(Graph* from, Graph* to);
	// ����
	static Graph* bingLink(Graphes& graphes);
	// �ظ� TODO: Debug
	static Graph* repeatLink(Graph* graph);

private:

};

