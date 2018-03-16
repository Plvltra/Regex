#pragma once

#include "EpsilonNFA.h"
#include "DFAMatrix.h"

class DFAGraph
{
public:
	DFAGraph(GraphPtr NFAGraph);

private:
	StatPtr start;
	DFAMatrix matrix;
};
