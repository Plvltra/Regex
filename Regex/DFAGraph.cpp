
#include "Graph.h"
#include "DFAMatrix.h"

using namespace std;

DFAGraph::DFAGraph(NFAGraphPtr NFAGraph)
{
	matrix = makeMatrix(NFAGraph);
	startStat = matrix->buildDFAGraph();
	assignID();
}
