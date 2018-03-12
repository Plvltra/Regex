#pragma once

#include "EpsilonNFA.h"
#include "DataType.h"
#include "LinkManager.h"

class GraphManager
{
public:
	static void epsToNFA(Graph* graph);
	static void printGraph(Graph* graph);
	// 串联
	static Graph* chuanLink(Graph* from, Graph* to);
	// 并联
	static Graph* bingLink(Graphes& graphes);
	// 重复 TODO: Debug
	static Graph* repeatLink(Graph* graph);

private:

};

