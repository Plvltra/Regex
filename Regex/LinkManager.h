#pragma once

#include "EpsilonNFA.h"
#include "DataType.h"

class LinkManager
{
public:
	// ��������״̬
	static void link(StatPtr from, StatPtr to, Type content);
	/* ɾ���������߲��ͷűߣ� ���ƻ������� */
	static void deleteLink(StatPtr stat1, StatPtr stat2);
	/* ɾ��һ������ */
	static void deleteLinks(StatPtr stat, Stats& stats);
	/* �Ͽ��������Ӳ���ǰ������ߵĺ�̽ڵ�����
	   ������������end�򴫵�״̬ */
	static void skipStat(StatPtr from, StatPtr beSkiped);
	/* ��ͼ��ɾȥĳ�ڵ㣬����ǰ�ýڵ�����ýڵ�����
	   ����ɾ������end��ת��״̬ */
	static void eraseStat(StatPtr stat);
	// Function
	static bool isLinked(StatPtr stat1, StatPtr stat2);
	/* @return: NULL˵��ǰ�����߲����� */
	static EdgePtr getLink(StatPtr stat1, StatPtr stat2);
	static Type getLinkCont(StatPtr stat1, StatPtr stat2);

private:
	// ���ĳ״̬ʹ����ǰ��״̬����,������ɾ��
	static void cross(StatPtr from, StatPtr beCrossed);
	static void deleteElem(Edges& edges, EdgePtr elem);
	//---------------------- Debug ----------------------//
	static int level;
	static void tab(int n);
	static void debug(std::string s);
};