#pragma once

#include "EpsilonNFA.h"

class LinkManager
{
public:
	// ��������״̬
	static void link(StatPtr from, StatPtr to, Type content);
	/* ɾ������ָ�����ߣ� ���ƻ������� */
	static void deleteLink(StatPtr from, StatPtr to, Type content);
	/* ɾ���������ߣ� ���ƻ������� */
	static void deleteLink(StatPtr from, StatPtr to); // ˫��
	/* ɾ��һ������ */
	static void deleteLinks(StatPtr stat, Stats& stats);  // ˫��
	/* �Ͽ��������ӣ�(���������ӣ���ǰ������ߵĺ�̽ڵ�����)
	������������end�򴫵�״̬ */
	static void skipStat(StatPtr from, StatPtr beSkiped);
	/* �Ͽ�����ָ�����ݵ����ӣ�(�����ڴ������ӣ���ǰ������ߵĺ�̽ڵ�����)
	������������end�򴫵�״̬ */
	static void skipStat(StatPtr from, StatPtr beSkiped, Type content);
	/* ��ͼ��ɾȥĳ�ڵ㣬����ǰ�ýڵ�����ýڵ�����
	   ����ɾ������end��ת��״̬ */
	static void eraseStat(StatPtr stat);
	// Function
	static bool isLinked(StatPtr stat1, StatPtr stat2); // ˫��
	// ��������, return: NULL˵��ǰ�����߲����� 
	static Edges getLink(StatPtr from, StatPtr to);
	static Conts getLinkCont(StatPtr from, StatPtr to);

private:
	// ���ĳ״̬ʹ����ǰ��״̬����,������ɾ��
	static void cross(StatPtr from, StatPtr beCrossed);
	static void deleteElem(Edges& edges, EdgePtr elem);
	//---------------------- Debug ----------------------//
	static int level;
	static void tab(int n);
	static void debug(std::string s);
};