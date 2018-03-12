#pragma once

#include "EpsilonNFA.h"
#include "DataType.h"

class LinkManager
{
public:
	// ��������״̬
	static void link(Status* from, Status* to, Type content);
	static void link(Status* from, Stats& tos, Conts& contents);
	// �ݹ�ɾ��ĳһ״̬��̵�epsilon��
	static void deleteEps(Status* currStat);
	// Function
	static bool isLinked(Status* stat, Status* nextStat);
	static StatusEdge* getLink(Status* stat, Status* nextStat);
	/* ɾ���������߲��ͷűߣ� ���ƻ������� */
	static void deleteLink(Status* stat, Status* nextStat);
	static void deleteLink(Status* stat, Stats& nextStats);
};