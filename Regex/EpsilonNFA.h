#pragma once
#include <vector>
#include <string>
#include <queue>
#include <memory>
#include <exception>

#include "Debug.h"
#include "StatSet.h"
#include "Graph.h"
#include "DataType.h"

typedef char Type;
const Type epsilon = '*';

class Status;
class StatusEdge;
class Graph;
class StatSet;
typedef std::shared_ptr<StatSet> StatSetPtr;
typedef std::shared_ptr<Status> StatPtr;
typedef std::shared_ptr<StatusEdge> EdgePtr;
typedef std::shared_ptr<Graph> GraphPtr;

typedef std::vector<EdgePtr> Edges;
typedef std::vector<StatPtr> Stats;
typedef std::vector<GraphPtr> Graphes;
typedef std::vector<Type> Conts;
typedef std::queue<StatPtr> StatQue;

typedef void StatDealer(StatPtr);

inline StatPtr makeStatPtr()
{
	return std::make_shared<Status>();
}

inline StatPtr makeStatPtr(bool isEnd, int ID)
{
	return std::make_shared<Status>(isEnd, ID);
}

inline GraphPtr makeGraphPtr(StatPtr start)
{
	return std::make_shared<Graph>(start);
}

inline GraphPtr makeGraphPtr(StatPtr start, StatPtr end)
{
	return std::make_shared<Graph>(start, end);
}

inline EdgePtr makeEdgePtr(Type content, StatPtr fromStat, StatPtr toStat)
{
	return std::make_shared<StatusEdge>(content, fromStat, toStat);
}