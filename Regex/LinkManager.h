#pragma once

#include "EpsilonNFA.h"
#include "DataType.h"

class LinkManager
{
public:
	// ��������״̬
	static void link(Status* from, Status* to, Type content);
	/* ɾ���������߲��ͷűߣ� ���ƻ������� */
	static void deleteLink(Status* stat1, Status* stat2);
	/* ɾ��һ������ */
	static void deleteLinks(Status* stat, Stats& stats);
	/* �Ͽ��������Ӳ���ǰ������ߵĺ�̽ڵ�����
	   ������������end�򴫵�״̬ */
	static void skipStat(Status* from, Status* beSkiped);
	/* ��ͼ��ɾȥĳ�ڵ㣬����ǰ�ýڵ�����ýڵ�����
	   ����ɾ������end��ת��״̬ */
	static void eraseStat(Status* stat);
	// Function
	static bool isLinked(Status* stat1, Status* stat2);
	/* @return: NULL˵��ǰ�����߲����� */
	static StatusEdge* getLink(Status* stat1, Status* stat2);
	static Type getLinkCont(Status* stat1, Status* stat2);

private:
	// ���ĳ״̬ʹ����ǰ��״̬����,������ɾ��
	static void cross(Status* from, Status* beCrossed);
	static void deleteElem(Edges& edges, StatusEdge* elem);
	//---------------------- Debug ----------------------//
	static int level;
	static void tab(int n);
	static void debug(std::string s);
};