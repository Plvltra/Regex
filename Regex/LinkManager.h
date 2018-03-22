#pragma once

#include "EpsilonNFA.h"

class LinkManager
{
public:
	// 连接两个状态
	static void link(StatPtr from, StatPtr to, Type content);
	/* 删除两者指定连线， 会破坏迭代器 */
	static void deleteLink(StatPtr from, StatPtr to, Type content);
	/* 删除两者连线， 会破坏迭代器 */
	static void deleteLink(StatPtr from, StatPtr to); // 双向
	/* 删除一组连接 */
	static void deleteLinks(StatPtr stat, Stats& stats);  // 双向
	/* 断开两者连接，(若存在连接，将前者与后者的后继节点连接)
	若被跳过的是end则传递状态 */
	static void skipStat(StatPtr from, StatPtr beSkiped);
	/* 断开两者指定内容的连接，(若存在此种连接，将前者与后者的后继节点连接)
	若被跳过的是end则传递状态 */
	static void skipStat(StatPtr from, StatPtr beSkiped, Type content);
	/* 在图中删去某节点，将其前置节点与后置节点连接
	   若被删除的是end则转移状态 */
	static void eraseStat(StatPtr stat);
	// Function
	static bool isLinked(StatPtr stat1, StatPtr stat2); // 双向
	// 单向连接, return: NULL说明前后两者不连接 
	static Edges getLink(StatPtr from, StatPtr to);
	static Conts getLinkCont(StatPtr from, StatPtr to);

private:
	// 跨接某状态使得其前后状态连接,不包含删除
	static void cross(StatPtr from, StatPtr beCrossed);
	static void deleteElem(Edges& edges, EdgePtr elem);
	//---------------------- Debug ----------------------//
	static int level;
	static void tab(int n);
	static void debug(std::string s);
};