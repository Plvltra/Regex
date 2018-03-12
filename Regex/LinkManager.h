#pragma once

#include "EpsilonNFA.h"
#include "DataType.h"

class LinkManager
{
public:
	// 连接两个状态
	static void link(Status* from, Status* to, Type content);
	static void link(Status* from, Stats& tos, Conts& contents);
	// 递归删除某一状态后继的epsilon边
	static void deleteEps(Status* currStat);
	// Function
	static bool isLinked(Status* stat, Status* nextStat);
	static StatusEdge* getLink(Status* stat, Status* nextStat);
	/* 删除两者连线并释放边， 会破坏迭代器 */
	static void deleteLink(Status* stat, Status* nextStat);
	static void deleteLink(Status* stat, Stats& nextStats);
};