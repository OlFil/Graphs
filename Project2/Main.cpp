#include "gr.h"
#include "Dinic.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;
void IsolVert(Graph gr1) {
	cout << "\n Изолированные вершины " << endl;
	vector <string> is = gr1.isolir();
	for (int i = 0; i < is.size(); i++) {
		cout << is[i] << " ";
	}
}

void Nooses(Graph gr1) {
	vector <string> no = gr1.noose();
	cout << "\n Петли " << endl;
	for (int i = 0; i < no.size(); i++) {
		cout << no[i] << " ";
	}
}

Graph simRas(Graph g1, Graph g2) {
	map<string, int> ff;
	map<string, map<string, int>> result;
	map<string, map<string, int>> G1= g1.GetAL();
	for (auto it = G1.begin(); it != G1.end(); ++it) {
		map<string, int> tmpG1 = g1.GetAL().find(it->first)->second;
		map<string, int> tmpG2 = g2.GetAL().find(it->first)->second;
		map<string, int> tmp;
		for (auto jt = tmpG1.begin(); jt != tmpG1.end(); ++jt)
		{
			if (tmpG2.find(jt->first) == tmpG2.end())
			{
				tmp.insert(make_pair(jt->first, jt->second));
			}
			else tmpG2.erase(jt->first);
		}
		tmp.insert(tmpG2.begin(), tmpG2.end());
		result.insert(make_pair(it->first, tmp));
	}
	Graph res(result, g1.getDir(), g1.getM());
	return res;
}


Graph creating() {
	bool dir, m;
	int n;
	cout << "Работаем с неориентированным или с ориентированным графом? 0 - неор, 1 - ор \n";
	cin >> n;
	string s;
	if (n == 1) {
		dir = true;
		s = "or.txt";
	}
	else {
		dir = false;
		s = "gr.txt";
	}
	cout << "Взвешенный? 0 - нет, 1 - да \n";
	cin >> n;
	if (n == 1) {
		m = true;
	}
	else {
		m = false;
	}

	if (dir == true && m == true) //s = "floid.txt";
	//s="or1.txt";
	s = "flow1.txt";
	else
		if (dir == false && m == true) s = "gr.txt"; 
	//s = "ostov.txt";
		else
			if (dir == true && m == false) s = "orNM.txt";
			else
				s = "grNM.txt";

	ifstream in(s);
	string key1, key2, type;
	int value;
	map <string, map<string, int>> graph;
	cout << "Создаем граф сами или из файла? 0-ручками, 1 - из файла\n";
	cin >> n;
	Graph gr1;
	//консольный ввод
	/*if (n == 0) {
		while (n != -1) {
			map  <string, int> ff;
			cin >> key1;
			while (n != 0) {
				cin >> key2;
				cin >> value;
				ff.insert(make_pair(key2, value));
				cout << "еще смежные? 1 - да, 0 -нет;";
				cin >> n;
			}
			graph.insert(make_pair(key1, ff));
			cout << "еще вершины? 1 - да, -1 -нет;";
			cin >> n;
		}
	}
	else {*/

	if (n == 1) {
		while (in.peek() != EOF) {
			in >> key1;
			map  <string, int> ff;
			while (in.peek() != '\n') {
				in >> key2 >> value;
				ff.insert(make_pair(key2, value));
				if (in.peek() == EOF) break;
			}
			graph.insert(make_pair(key1, ff));
		}
		gr1 = Graph(graph, dir, m);
	}
	return gr1; 
}

Graph changing(Graph gr1) {
	int n;
	cout << "1-добавить верш," << endl;
	cout << "2 - добав ребро," << endl;
	cout << "3 - удал верш," << endl;
	cout << "4 - удал ребро," << endl;
	cout << "5 - запись в файл," << endl;
	cout << "6 - вывод в консоль," << endl;
	cout << "7 - Задания на обход в глубину," << endl;
	cout << "8 - Задания на обход в ширину," << endl;
	cout << "9 - Алгоритм Краскала," << endl;
	cout << "10 - Алгоритм Дейкстры,"<<endl;
	cout << "11 - Алгоритм Форда-Беллмана," << endl;
	cout << "12 - Алгоритм Флойда-Уоршелла," << endl;
	cout << "13 - Потоковый алгоритм" << endl;
	cout << "14 - Изолированные вершины" << endl;
	cout << "15 - Петли" << endl;
	cout << "0 - выход " << endl;
	while (1) {
		cin >> n;
		if (n == 1) {
			cout << "Введите вершину \n";
			string v;
			cin >> v;
			gr1.addV(v);
			cout << "Успешно. Что-то еще? \n";
		}
		else
			if (n == 2) {
				cout << "Введите выершины (и вес ребра, если взвеш) \n";
				string v1, v2;
				int w;
				if (gr1.getM())
					cin >> v1 >> v2 >> w;
				else {
					cin >> v1 >> v2;
					w = 0;
				}
				gr1.addR(v1, v2, w);
				cout << "Успешно. Что-то еще? \n";
			}
			else
				if (n == 3) {
					cout << "Введите вершину \n";
					string v;
					cin >> v;
					gr1.delV(v);
					cout << "Успешно. Что-то еще? \n";
				}
				else
					if (n == 4) {
						cout << "Введите вершины \n";
						string v1, v2;
						cin >> v1 >> v2;
						gr1.delR(v1, v2);
						cout << "Успешно. Что-то еще? \n";
					}
					else
						if (n == 5) {
							gr1.rec();
							cout << "Успешно. Что-то еще? \n";
						}
						else
							if (n == 6) {
								gr1.print();
								cout << "Успешно. Что-то еще? \n";
							}
							else
								if (n == 7) {
									cout << "В какую вершину пойдем?\n";
									string start;
									cin >> start;
									cout << "В нее можно попасть из \n";
									gr1.bfs(start);
									cout << endl;
									

								}
		if (n == 8) {
			cout << "В какую вершину пойдем?\n";
			string start, u1, u2;
			cin >> start;
			cout << "Введите две вершины, а я угадаю, из какой до стартовой быстрее доехать\n";
			cin >> u1 >> u2;
			cout << gr1.lessPath(u1, u2, start) << endl;
		}
		if (n == 9) {
			gr1.Kruskal();
		}
		if (n == 10) {
			//cout << "Введите стартовую вершину ";
			//string start;
			//cin >> start;
			//gr1.Deikstra(start);
			gr1.pathes();
		}
		if (n == 11) {
			cout << "Введите стартовую вершину ";
			string start;
			cin >> start;
			gr1.FordBellman(start);
		}
		if (n == 12) {
			gr1.TaskFloid();
		}
		if (n == 13) {
			V(gr1);
		}
		if (n == 14) {
			IsolVert(gr1);
		}
		if (n == 15) {
			Nooses(gr1);
		}
								if (n == 0) { break; }//return 0;
								//else { cout << "Недопустимая операция! \n"; }

	}
	return gr1;
}





int main() {
	setlocale(LC_ALL, "rus");

	Graph Graph111=creating();
	Graph111.print();
	cout << " ";
	Graph111 =changing(Graph111);
	//Graph111.Kruskal();
	/*cout << "В какую вершину пойдем?\n";
	string start,u1,u2;
	cin >> start;
	cout << "В нее можно попасть из \n";
	Graph111.bfs(start);
	cout << endl;
	cout << "Введите две вершины, а я угадаю, из какой до стартовой быстрее доехать\n";
	cin >> u1 >> u2;
	cout << Graph111.lessPath(u1, u2, start)<<endl;*/
	
	/*cout << "Теперь получим симметрическую разность для двух графов, создадим их!" << endl;
	bool dir, m;
	int n;
	cout << "Работаем с неориентированным или с ориентированным графом? 0 - неор, 1 - ор \n";
	cin >> n;
	string s, s2;
	if (n == 1) {
		dir = true;
		s = "orS.txt";
		s2 = "orS1.txt";
	}
	else {
		dir = false;
		s = "gr.txt";
		s2 = "gr1.txt";
	}
	cout << "Взвешенный? 0 - нет, 1 - да \n";
	cin >> n;
	if (n == 1) {
		m = true;
	}
	else {
		m = false;
	}

	if (dir == true && m == true) {
		s = "orS.txt";
		s2 = "orS1.txt";
	}
	else
		if (dir == false && m == true) {
			s = "gr.txt";
			s2 = "gr1.txt";
		}
		else
			if (dir == true && m == false) {
				s = "orNM.txt";
				s2 = "orNM1.txt";
			}
			else {
				s = "grNM.txt";
				s2 = "grNM1.txt";
			}

	ifstream in(s);
	string key1, key2, type;
	int value;
	map <string, map<string, int>> graph;
	map <string, map<string, int>> graph1;
	cout << "Создаем граф сами или из файла? 0-ручками, 1 - из файла\n";
	cin >> n;
	Graph gr1, gr2;
	
	if(n==1){
		while (in.peek() != EOF) {
			in >> key1;
			map  <string, int> ff;
			while (in.peek() != '\n') {
				in >> key2 >> value;
				ff.insert(make_pair(key2, value));
				if (in.peek() == EOF) break;
			}
			graph.insert(make_pair(key1, ff));
		}
		gr1 = Graph (graph, dir, m);
	}
	
	in.close();
	ifstream in1(s2);
	if (n == 1) {
		while (in1.peek() != EOF) {
			in1 >> key1;
			map  <string, int> ff;
			while (in1.peek() != '\n') {
				in1 >> key2 >> value;
				ff.insert(make_pair(key2, value));
				if (in1.peek() == EOF) break;
			}
			graph1.insert(make_pair(key1, ff));
		}
		gr2 = Graph(graph1, dir, m);
	}
	gr1.print();
	cout << endl;
	gr2.print();
	cout << endl;
	Graph G12 = simRas(gr1, gr2);
	cout << "Симметрическая разность графов " << endl;
	G12.print();*/
/*
	cout << "\n Изолированные вершины "<<endl;
	vector <string> is = gr1.isolir();
	for (int i = 0; i < is.size(); i++) {
		cout << is[i] << " ";
	}
	vector <string> no = gr1.noose();
	cout << "\n Петли "<<endl;
	for (int i = 0; i < no.size(); i++) {
		cout << no[i] << " ";
	}*/
	system("pause");
	return 0;
}

