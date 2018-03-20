#pragma once

#include "EpsilonNFA.h"
#include "Graph.h"

class GraphManager
{
public:
	// ����
	static GraphPtr chuanLink(GraphPtr from, GraphPtr to);
	// ����
	static GraphPtr bingLink(GraphPtr g1, GraphPtr g2);
	static GraphPtr bingLink(Graphes graphes);
	// �ظ� TODO: Debug
	static GraphPtr repeatLink(GraphPtr graph);
	// ��ѡ
	static GraphPtr chooseLink(GraphPtr graph);

private:

};

