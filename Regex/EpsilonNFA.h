#pragma once
#include <vector>
#include <string>
#include <queue>
#include <exception>

#include "Debug.h"

typedef char Type;
const Type epsilon = '*';

class Status;
class StatusEdge;
class Graph;
typedef std::vector<StatusEdge*> Edges;
typedef std::vector<Status*> Stats;
typedef std::vector<Graph*> Graphes;
typedef std::vector<Type> Conts;
typedef std::queue<Status*> StatQue;

typedef void StatDealer(Status*);
