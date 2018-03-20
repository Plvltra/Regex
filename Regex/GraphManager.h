#pragma once

#include "EpsilonNFA.h"
#include "Graph.h"

class GraphManager
{
public:
	// 串联
	static GraphPtr chuanLink(GraphPtr from, GraphPtr to);
	// 并联
	static GraphPtr bingLink(GraphPtr g1, GraphPtr g2);
	static GraphPtr bingLink(Graphes graphes);
	// 重复 TODO: Debug
	static GraphPtr repeatLink(GraphPtr graph);
	// 可选
	static GraphPtr chooseLink(GraphPtr graph);

private:

};

