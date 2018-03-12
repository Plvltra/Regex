#pragma once

#include "EpsilonNFA.h"
#include "DataType.h"

class LinkManager
{
public:
	// 连接两个状态
	static void link(Status* from, Status* to, Type content);
	// 跨接某状态使得其前后状态连接,不包含删除
	static void cross(Status* from, Status* beCrossed);
	/* 断开两者连接并将前者与后者的后继节点连接
	   若被跳过的是end则传递状态 */
	static void skipStat(Status* from, Status* beSkiped);
	// 连接某状态与一组状态
	//static void link(Status* from, Stats& tos, Conts& contents);
	// 在图中删去某节点，将其前置节点与后置节点连接
	static void eraseStat(Status* stat);
	// Function
	static bool isLinked(Status* stat1, Status* stat2);
	/* @return: NULL说明前后两者不连接 */
	static StatusEdge* getLink(Status* stat1, Status* stat2);
	static Type getLinkCont(Status* stat1, Status* stat2);
	/* 删除两者连线并释放边， 会破坏迭代器 */
	static void deleteLink(Status* stat1, Status* stat2);
	/* 删除一组连接 */
	static void deleteLinks(Status* stat, Stats& stats);

private:
	static void deleteElem(Edges& edges, StatusEdge* elem);

};