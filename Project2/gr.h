#pragma once
#include <iostream>
#include <map>
#include<vector>
#include <fstream>
#include <queue>
#include <stack>
using namespace std;
class Graph {
private:
	map <string, map<string, int>> AdjacensyList;
	bool direct;
	bool measured;

public:
	
	Graph(map <string, map<string, int>> a, bool d, bool m) {
		AdjacensyList = a;
		direct = d;
		measured = m;
	}
	Graph(const Graph& g) {
		this->AdjacensyList = g.AdjacensyList;
		this->direct = g.direct;
		this->measured = g.measured;

	}

	Graph() {
		AdjacensyList.clear();
		direct = false;
		measured = false;
	}
	~Graph()
	{
		direct = false;
		AdjacensyList.clear();
	}
	bool getDir();
	bool getM();
	map <string, map<string, int>> GetAL();
	void setDir (bool d);
	void setM (bool m);
	void addV(string v);
	void addR(string v1, string v2, int w);
	void delV(string v);
	void delR(string v1, string v2);
	void rec();
	bool existV(string v);
	bool existR(string v1, string v2);
	vector <string> isolir();
	vector<string> noose();
	void print();
	void bfs(string c);
	vector<string> DFS_path(string a, string b);
	vector<string> bfsPath(string c, string b);
	string lessPath(string u1, string u2, string c);
	void Kruskal();
	int getRebr();
	int	getVersh();
	void Deikstra(string start);
	void pathes();
	void FordBellman(string start);
	vector<vector<int> > Floid();
	void TaskFloid();
	vector<vector<int>> Matrix();
	vector<string> getList();
};
