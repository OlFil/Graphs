#pragma once
#include "gr.h"
const int INF = 1000000;
class Dinic {
public:
	int getS() { return s; }
	int getT() { return t; }
	void setS(int ns) { s = ns; }
	void setT(int nt) { t = nt; }
	Dinic(int ns, int nt, vector<vector<int>> nc);
	int flow();
private:
	int s, t, n;
	vector <vector <int>> c, f;
	vector <int> d, ptr, q;
	bool bfs();
	int dfs(int v, int flow);
};
Dinic::Dinic(int ns, int nt, vector <vector<int>> nc)
{
	s = ns;
	t = nt;
	c = nc;
	n = c.size();
	d.resize(n);
	ptr.resize(n);
	q.resize(n);
	f.resize(n);
	for (int i = 0; i < n; i++)
		f[i].resize(n);
}
bool Dinic::bfs() {
	int qh = 0, qt = 0;
	q[qt++] = s;
	fill_n(begin(d), n, -1);
	d[s] = 0;
	while (qh < qt) {
		int v = q[qh++];
		for (int to = 0; to < n; ++to)
			if (d[to] == -1 && f[v][to] < c[v][to]) {
				q[qt++] = to;
				d[to] = d[v] + 1;
			}
	}
	return d[t] != -1;
}
int Dinic::dfs(int v, int flow) {
	if (!flow) return 0;
	if (v == t) return flow;
	for (int& to = ptr[v]; to < n; ++to) {
		if (d[to] != d[v] + 1)
			continue;
		int pushed = dfs(to, min(flow, c[v][to] - f[v][to]));
		if (pushed) {
			f[v][to] += pushed;
			f[to][v] -= pushed;
			return pushed;
		}
	}
	return 0;
}
int Dinic::flow()
{
	int f = 0;
	while (true)
	{
		if (!bfs())
			break;
		fill_n(begin(ptr), n, 0);
		while (int pushed = dfs(s, INF))
			f += pushed;
	}
	return f;
}


void V(Graph g)
{
	auto c = g.Matrix();
	auto list = g.getList();
	int s = -1, t = -1;
	string P1, P2;
	/*for (auto& i : c)
		for (auto& j : i)
			if (j == INF)
				j = 0;*/
	while (s == -1 and t == -1)
	{
		int cnt = 0;
		cout << " ¬ведите две вершины: ";
		cin >> P1 >> P2;
		for (auto& l : list)
		{
			if (P1 == l)
				s = cnt;
			if (P2 == l)
				t = cnt;
			cnt++;
		}
	}
	Dinic d(s, t, c);
	int flow = d.flow();
	cout << flow << endl;
}
