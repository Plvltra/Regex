
#include "Graph.h"
#include "DFAGraph.h"

using namespace std;

DFAGraph::DFAGraph(GraphPtr NFAGraph)
	:matrix(NFAGraph)
{
	start = matrix.buildDFAGraph();
}
