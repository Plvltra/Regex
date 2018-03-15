#pragma once

#include "EpsilonNFA.h"
#include "DataType.h"
#include "LinkManager.h"
#include "Graph.h"

class GraphManager
{
public:
	// 串联
	static GraphPtr chuanLink(GraphPtr from, GraphPtr to);
	// 并联
	static GraphPtr bingLink(Graphes& graphes);
	// 重复 TODO: Debug
	static GraphPtr repeatLink(GraphPtr graph);

private:

};

