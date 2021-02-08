#include "gr.h"

bool Graph::getDir() {
	return this->direct;
}
bool Graph::getM() {
	return this->measured;
}
void Graph::setDir(bool d) {
	this->direct = d;
}
void Graph::setM(bool m) {
	this->measured = m;
}

map <string, map<string, int>> Graph::GetAL() {
	return this->AdjacensyList;
}

vector<vector<int>> Graph::Matrix() {
	int	n = getVersh();
	map<string, int> names;
	int i = 0;
	for (auto it = AdjacensyList.begin(); it != AdjacensyList.end(); ++it) {
		names.insert(make_pair(it->first, i));
		i++;
	}
	vector<vector<int>> d(n, vector<int>(n, 0));
	for (auto it = AdjacensyList.begin(); it != AdjacensyList.end(); ++it)
		for (auto jt = it->second.begin(); jt != it->second.end(); ++jt) {
			d[names[it->first]][names[jt->first]] = jt->second;
		}
	return d;
}
vector<string> Graph::getList() {
	vector<string> names;
	for (auto it = AdjacensyList.begin(); it != AdjacensyList.end(); ++it) {
		names.push_back(it->first);
	}
	return names;
}

vector<string> Graph::DFS_path(string start, string end)
{
	vector<string> path;
	map<string, bool> used;
	map<string, string> p;
	stack<string> s;
	s.push(start);
	p[start] = "-1";
	used[start] = true;
	while (!s.empty())
	{
		string v = s.top();
		s.pop();
		map <string, map <string, int>>::iterator it = AdjacensyList.find(v);
		for (auto jt = it->second.begin(); jt != it->second.end(); ++jt) 
		{
			string to = jt->first;
			if (!used[to])
			{
				s.push(to);
				used[to] = true;
				p[to] = v;
			}
		}
	}
	string cur = end;         //текущая вершина пути
	while (p[cur] != "-1") {   //пока существует предыдущая вершина
		cur = p[cur];        //переходим в неё
		path.push_back(cur);    //и дописываем к пути
	}
	reverse(path.begin(), path.end());
	return path;
}

int Graph::getVersh() {
	return AdjacensyList.size();

}
int Graph::getRebr() {
	int m = 0;
	//map <string, map <string, int>>::iterator it = AdjacensyList.begin();
	for (auto it = AdjacensyList.begin(); it != AdjacensyList.end(); ++it)
	for (auto jt = it->second.begin(); jt != it->second.end(); ++jt) {
		m++;
	}
	return m;
}

void Graph::Deikstra(string start){//Вывести длины кратчайших путей для всех пар вершин.
	int m = getRebr();
	int	n = getVersh();
	map<string, int> d;
	map<string, string> p;
	map<string, bool> u;
	vector<string>vertexes;
	for (auto it = AdjacensyList.begin(); it != AdjacensyList.end(); ++it) {
		vertexes.push_back(it->first);
	}
	for (auto it = AdjacensyList.begin(); it != AdjacensyList.end(); ++it) {
		d.insert(make_pair(it->first, INT_MAX));
	}
	for (auto it = AdjacensyList.begin(); it != AdjacensyList.end(); ++it) {
		u.insert(make_pair(it->first, false));
	}
	d[start] = 0;
	for (int i = 0; i < n; i++) {
		string v = "!!!";
		for (int j = 0; j < n; j++) {
			if (!u[vertexes[j]] && (v == "!!!" || d[vertexes[j]] < d[v]))
				v = vertexes[j];
		}
		if (d[v] == INT_MAX)
			break;
		u[v] = true;
		map <string, map <string, int>>::iterator it = AdjacensyList.find(v);
		for (auto jt = it->second.begin(); jt != it->second.end(); ++jt) {
			map <string, int> a = it->second;
			string to =jt->first;
			int len = jt->second;
			if (d[v] + len < d[to]) {
				d[to] = d[v] + len;
				p.insert(make_pair(to,v));
			}
		}
	}
	cout << "Длины кратчайших путей от вершины " << start << " до:" << endl; 
	for (auto it = d.begin(); it != d.end(); ++it) {
		cout << it->first << " - " << it->second<<endl;
	}
}

void Graph::pathes() {
	for (auto it = AdjacensyList.begin(); it != AdjacensyList.end(); ++it) {
		Deikstra(it->first);
		cout << endl;
	}
}

void Graph::FordBellman(string start) { /*Вывести все кратчайшие пути из вершины u.*/
	vector <pair <int, pair <string, string>>> g;
	int m = getRebr();
	int	n = getVersh();
	map<string, int> d;
	map<string, string> p;
	for (auto it = AdjacensyList.begin(); it != AdjacensyList.end(); ++it)
		for (auto jt = it->second.begin(); jt != it->second.end(); ++jt) {
			g.push_back(make_pair(jt->second, make_pair(it->first, jt->first)));

		}
	for (auto it = AdjacensyList.begin(); it != AdjacensyList.end(); ++it) {
		d.insert(make_pair(it->first, INT_MAX));
	}
	for (auto it = AdjacensyList.begin(); it != AdjacensyList.end(); ++it) {
		p.insert(make_pair(it->first, "none"));
	}
	d[start] = 0;
	for (;;) {
		bool any = false;
		for (int j = 0; j < m; j++) {
		if(d[g[j].second.first] < INT_MAX)
			if (d[g[j].second.second] > d[g[j].second.first] + g[j].first) {
				d[g[j].second.second] = d[g[j].second.first] + g[j].first;
				p[g[j].second.second] = g[j].second.first;
				any = true;
			}
		}
		if (!any) break;
	}
	for (auto it = d.begin(); it != d.end(); ++it) {

		if (d[it->first] == 0)
			cout << "Нет пути из " << start << " в " << it->first << "."<<endl;
		else {
			vector<string> path;
			for (string cur = it->first; cur != "none"; cur = p[cur])
				path.push_back(cur);
			reverse(path.begin(), path.end());

			cout << "Из " << start << " в " << it->first << ": " << endl;
			for (size_t i = 0; i < path.size(); ++i)
				cout << path[i] << ' ';
			cout << endl;
		}
	}

	//cout << "Длины кратчайших путей от верщины " << start << " до:" << endl;/*не длины, а пути восстановит!ь*/
	//for (auto it = d.begin(); it != d.end(); ++it) {
	//	cout << it->first << " - " << it->second << endl;
	//}
}

vector<vector<int>> Graph::Floid() { /*Определить множество вершин орграфа, расстояние от которых до заданной вершины не более N.*/
	//представление графа матрицей смежности
	int	n = getVersh();
	map<string,int> names;
	int i = 0;
	for (auto it = AdjacensyList.begin(); it != AdjacensyList.end(); ++it) {
		names.insert(make_pair(it->first, i));
		i++;
	}
	vector<vector<int> > d(n, vector<int>(n, INT_MAX));
	for (int i = 0; i < n; i++) 
		for(int j = 0; j < n;j++){
			if (i == j) 
				d[i][j] = 0;
		}
	for (auto it = AdjacensyList.begin(); it != AdjacensyList.end(); ++it)
		for (auto jt = it->second.begin(); jt != it->second.end(); ++jt) {
			d[names[it->first]][names[jt->first]] = jt->second;
		}
	/*сам алгоритм*/
	for (int k = 0; k < n; ++k)
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (d[i][k] < INT_MAX && d[k][j] < INT_MAX)
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
	
	//циклы отрицателньго веса
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			for (int t = 0; t < n; ++t)
				if (d[i][t] < INT_MAX && d[t][t] < 0 && d[t][j] < INT_MAX)
					d[i][j] = INT_MIN;
	return d;
}
void Graph::TaskFloid() {
	int	n = getVersh();
	vector<vector<int>> g = Floid();
	for (int i = 0; i < n; ++i) {
		cout << endl;
		for (int j = 0; j < n; ++j)
			cout << g[i][j] << " ";
	}
	cout << endl;
	map<string, int> names;
	vector <string> INTnames;
	int i = 0;
	for (auto it = AdjacensyList.begin(); it != AdjacensyList.end(); ++it) {
		names.insert(make_pair(it->first, i));
		i++;
		INTnames.push_back(it->first);
	}
	
	cout << "Введите стартовую вершину " << endl;
	string start;
	cin >> start;
	cout << "Введите N " << endl;
	int j = names[start];
	int N;
	cin >> N;
	vector<string> vertexes;
	for (int i = 0; i < n; i++) {
		if (g[i][j] <= N && g[i][j]!=INT_MIN && g[i][j]!=0) {
			vertexes.push_back(INTnames[i]);
		}
	}
	cout<<"вершины орграфа, расстояние от которых до заданной вершины не более N "<<endl;
	for (int i = 0; i < vertexes.size(); i++) {
		cout << vertexes[i] << " ";
	}
}

void Graph::Kruskal() {
	int m = getRebr();
	int	n= getVersh();
	int i = 0;
	vector <pair <int, pair <string, string>>> g;
	for (auto it = AdjacensyList.begin(); it != AdjacensyList.end(); ++it)
		for (auto jt = it->second.begin(); jt != it->second.end(); ++jt) {
			g.push_back(make_pair(jt->second, make_pair(it->first, jt->first)));

		}
	vector <pair<string, string>> res;
	sort(g.begin(), g.end());
	map<string, int> tree_id;
	for (auto it = AdjacensyList.begin(); it != AdjacensyList.end(); ++it) {
		tree_id.insert(make_pair(it->first, i));
		i++;
	}

	for (int i = 0; i < m; i++) {
		string a = g[i].second.first, b = g[i].second.second;
		int l = g[i].first;
		if (tree_id[a] != tree_id[b])
		{
			res.push_back(make_pair(a, b));
			int old_id = tree_id[b], new_id = tree_id[a];
			for (auto jt = tree_id.begin(); jt != tree_id.end(); ++jt) {
				if (jt->second == old_id)
					jt->second = new_id;
		}
	}
}
	cout << "Остовное дерево " << endl;
	for (int i = 0; i < res.size(); i++) {
		cout << res[i].first << " - " << res[i].second << endl;
	}
	if (n - 1 == res.size()) {
		cout << "Это дерево";
	}
	else cout << "Это лес";

}


vector<string> Graph::bfsPath(string c, string b) {
	vector<string> path;
	if (existV(c) && existV(b)) {
		queue<string> q;
		q.push(c);
		map<string, bool> used;
		map<string, string> p;
		map <string, int> d;
		used[c] = true;
		p[c] = "-1";
		while (!q.empty()) {
			string v = q.front();
			q.pop();
			map <string, map <string, int>>::iterator it = AdjacensyList.find(v);
			for (auto jt = it->second.begin(); jt != it->second.end(); ++jt) {
				string to = jt->first;
				if (!used[to]) {
					used[to] = true;
					d[to] = d[v] + 1;
					q.push(to);
					p[to] = v;
				}
			}
		}
		string cur = b;         //текущая вершина пути
		//push_back(cur);
		while (p[cur] != "-1") {   //пока существует предыдущая вершина
			cur = p[cur];        //переходим в неё
			path.push_back(cur);    //и дописываем к пути
		}
		reverse(path.begin(), path.end());
		return path;
	}
	else {
		cout << "Вершин не существует!";
		return path;
	}
}

	
string Graph::lessPath(string u1, string u2, string c) {
	int U1 = bfsPath(u1, c).size();
	int U2 = bfsPath(u2, c).size();
	if (U1 >= U2) return u2;
	else return u1;
}

void Graph::bfs(string c) {
	//map<string, bool> used;
	for (auto it = AdjacensyList.begin(); it != AdjacensyList.end(); ++it) {
		if (!DFS_path(it->first, c).empty()) cout << it->first<< ", ";
	}
}


void Graph::addV(string v)
{
	if(!existV(v))
	{
		map <string, int> second;
		AdjacensyList.insert({ v, second });
	}
	else
		cout << " Вершина уже существует" << endl;
}

bool Graph::existV(string v)
{
	map <string, map <string, int>>::iterator i = AdjacensyList.find(v);
	return (!(i == AdjacensyList.end())) ;
}
bool Graph::existR(string v1, string v2)
{
	if (!existV(v1) || !existV(v2))
		return false;
	else {
		map <string, map <string, int>>::iterator i = AdjacensyList.find(v1);
		map <string, map <string, int>>::iterator j = AdjacensyList.find(v2);
		bool ex1 = false;
		bool ex2 = false;
		for (auto it = i->second.begin(); it != i->second.end(); ++it)
			if (it->first == v2) ex1 = true;
		for (auto jt = j->second.begin(); jt != j->second.end(); ++jt)
			if (jt->first == v1) ex2 = true;
		if (direct) return ex1;
		if (ex1 == true || ex2 == true) return true;
		else return false;
		//else return (ex1 && ex2);
	}
}




void Graph::addR(string v1, string v2, int w)
{
	if (!existV(v1) || !existV(v2))
		cout << "Вершин не существет!";
	else
	if (existR(v1, v2)) cout << "Ребро уже существет!";
		else
		{
			AdjacensyList.find(v1)->second.insert({ v2, w });
			if (!direct)
				AdjacensyList.find(v2)->second.insert({ v1, w });

		}
}

void Graph::delV(string v)
{
	if (existV(v)==false) cout << "Вершины не существует!";
	else
	{
		for (map <string, map <string, int>>::iterator out = AdjacensyList.begin(); out != AdjacensyList.end(); ++out)
			if (out->second.find(v) != out->second.end())
				out->second.erase(v);
		AdjacensyList.erase(v);
	}
}
void Graph::delR(string v1, string v2)
{
	if (existR(v1, v2))
	{
		map <string, map <string, int>>::iterator out;
		map <string, int>::iterator in;
		out = AdjacensyList.find(v1);
		in = out->second.find(v2);
		out->second.erase(in);
		if (!direct)
			AdjacensyList.find(v2)->second.erase(v1);
	}
	else cout << "Ребра не существует!";
}


vector <string> Graph::isolir() {
	vector<string> isol;
	if (direct) {
		for (auto it = AdjacensyList.begin(); it != AdjacensyList.end(); ++it)
			if (it->second.empty()) isol.push_back(it->first);
		for (auto it = AdjacensyList.begin(); it != AdjacensyList.end(); ++it)
			for (int i = 0; i < isol.size(); i++)
				if (it->second.find(isol[i]) != it->second.end()) isol.erase(isol.begin() + i);
	}
	else {
		for (auto it = AdjacensyList.begin(); it != AdjacensyList.end(); ++it)
			if (it->second.empty()) isol.push_back(it->first);
			}
	return isol;
}

vector <string> Graph::noose() {
	vector <string> n;
	for (auto it = AdjacensyList.begin(); it != AdjacensyList.end(); ++it) {
		if (it->second.find(it->first) != it->second.end()) n.push_back(it->first);
	}
	return n;
}


void Graph::rec()
{
	ofstream out("ready.txt");
	map <string, map <string, int>>::iterator i;
	map <string, int>::iterator j;
	for (auto it = AdjacensyList.begin(); it != AdjacensyList.end(); ++it) {
		out << it->first << " ";
		for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
			out << jt->first << " " << jt->second << " ";
		out << endl;
	}
}


void Graph::print() {
	for (auto it = AdjacensyList.begin(); it != AdjacensyList.end(); ++it) {
		cout << it->first << " - ";
		if(measured==true)
			for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
				cout << jt->first << " " << jt->second << " ";
		else
			for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
				cout << jt->first << " ";
		cout << endl;
	}
}


