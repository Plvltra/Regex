#pragma once
#include <vector>
#include <string>
#include <queue>
#include <memory>
#include <exception>

#include "Debug.h"

typedef char Type;
const Type epsilon = '*';

class Status;
class StatusEdge;
class Graph;
class StatSet;
typedef std::vector<StatusEdge*> Edges;
typedef std::vector<Status*> Stats;
typedef std::vector<Graph*> Graphes;
typedef std::vector<Type> Conts;
typedef std::queue<Status*> StatQue;

typedef void StatDealer(Status*);
typedef std::shared_ptr<StatSet> StatSetPtr;
typedef std::shared_ptr<Status> StatPtr;
typedef std::shared_ptr<Graph> GraphPtr;
 
inline StatPtr makeStatPtr(bool isEnd, int ID)
{
	return std::make_shared<Status>(isEnd, ID);
}
