#pragma once

#include "EpsilonNFA.h"
#include "DataType.h"

class LinkManager
{
public:
	// ��������״̬
	static void link(Status* from, Status* to, Type content);
	// ���ĳ״̬ʹ����ǰ��״̬����,������ɾ��
	static void cross(Status* from, Status* beCrossed);
	/* �Ͽ��������Ӳ���ǰ������ߵĺ�̽ڵ�����
	   ������������end�򴫵�״̬ */
	static void skipStat(Status* from, Status* beSkiped);
	// ����ĳ״̬��һ��״̬
	//static void link(Status* from, Stats& tos, Conts& contents);
	// ��ͼ��ɾȥĳ�ڵ㣬����ǰ�ýڵ�����ýڵ�����
	static void eraseStat(Status* stat);
	// Function
	static bool isLinked(Status* stat1, Status* stat2);
	/* @return: NULL˵��ǰ�����߲����� */
	static StatusEdge* getLink(Status* stat1, Status* stat2);
	static Type getLinkCont(Status* stat1, Status* stat2);
	/* ɾ���������߲��ͷűߣ� ���ƻ������� */
	static void deleteLink(Status* stat1, Status* stat2);
	/* ɾ��һ������ */
	static void deleteLinks(Status* stat, Stats& stats);

private:
	static void deleteElem(Edges& edges, StatusEdge* elem);

};