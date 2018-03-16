#pragma once

#include "EpsilonNFA.h"
#include "DataType.h"
#include "LinkManager.h"
#include "Graph.h"

class GraphManager
{
public:
	// ����
	static GraphPtr chuanLink(GraphPtr from, GraphPtr to);
	// ����
	static GraphPtr bingLink(Graphes& graphes);
	// �ظ� TODO: Debug
	static GraphPtr repeatLink(GraphPtr graph);

private:

};

