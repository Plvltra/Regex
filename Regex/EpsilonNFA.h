#pragma once
#include <vector>
#include <string>
#include <queue>
#include <memory>
#include <exception>

#include "Debug.h"

typedef char Type;
const Type epsilon = '.';

class Status;
class StatusEdge;
class Graph;
class StatSet;
class NFAGraph;
class DFAGraph;
class DFAMatrix;

typedef std::shared_ptr<StatSet> StatSetPtr;
typedef std::shared_ptr<Status> StatPtr;
typedef std::shared_ptr<StatusEdge> EdgePtr;
typedef std::shared_ptr<Graph> GraphPtr;
typedef std::shared_ptr<NFAGraph> NFAGraphPtr;
typedef std::shared_ptr<DFAGraph> DFAGraphPtr;
typedef std::shared_ptr<DFAMatrix> DFAMatrixPtr;

typedef std::vector<EdgePtr> Edges;
typedef std::vector<StatPtr> Stats;
typedef std::vector<GraphPtr> Graphes;
typedef std::vector<Type> Conts;
typedef std::queue<StatPtr> StatQue;

typedef void StatDealer(StatPtr);

StatPtr makeStat();
StatPtr makeStat(bool isEnd, int ID);
NFAGraphPtr makeNFAGraph(GraphPtr graph);
DFAGraphPtr makeDFAGraph(NFAGraphPtr NFAGraph);
DFAMatrixPtr makeMatrix(NFAGraphPtr NFAGraph);
GraphPtr makeGraph(Type content);
GraphPtr makeGraph(StatPtr start, StatPtr end);
EdgePtr makeEdge(Type content, StatPtr fromStat, StatPtr toStat);
StatSetPtr makeStatSet(StatPtr stat);
