#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <string>
using namespace std;

const char epsilon = '\0';

struct Edge;
struct Status;
struct Graph;
struct Edge
{
	char content;
	Status *start;
	Status *end;
	Edge(char content, Status *start, Status *end)
		:content(content), start(start), end(end)
	{
	}
};
struct Status
{
	bool isEnd;
	vector<Edge*> inEdges;
	vector<Edge*> outEdges;
	Status():isEnd(false)
	{
	}
};
struct Graph
{
	Status *start;
	Status *end;
	Graph(Status *start, Status *end)
		: start(start), end(end)
	{
	}
};

Graph link(Status *src, Status *dest, char content)
{
	Edge *edge = new Edge(content, src, dest);
	src->outEdges.push_back(edge);
	dest->inEdges.push_back(edge);
	return Graph(src, dest);
}

Graph chuanLink(Graph src, Graph dest)
{
	Status *end1 = src.end;
	Status *start2 = dest.start;
	end1->isEnd = false;
	link(end1, start2, epsilon);
	return Graph(src.start, dest.end);
}

Graph bingLink(vector<Graph> graphes)
{
	Status *start = new Status();
	Status *end = new Status();
	end->isEnd = true;
	for (auto graph : graphes)
	{
		graph.end->isEnd = false;
		link(start, graph.start, epsilon);
		link(graph.end, end, epsilon);
	}
	return Graph(start, end);
}

//void repeat(Graph graph)
//{
//	Status *status = new Status();
//	Status *end = new Status();
//	end->isEnd = true;
//}



int main()
{
	
	//string src = "asduhb@qq.com";
	//string pattern = "([a-z,A-Z,0-9]+)@([a-z,A-Z,0-9]+).([a-z,A-Z,0-9]+)";
	//regex rgx(pattern);
	//smatch results;
	//regex_search(src, results, rgx);
	//for (auto result : results)
	//	cout << result << endl;
}