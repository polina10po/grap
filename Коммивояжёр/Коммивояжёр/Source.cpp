#include <glut.h>
#include "Graph.h"
#include <iostream>
#include <conio.h>
#include <locale>
#include <queue>
#include <stack>
#include "Print.h"
using namespace std;

Graph<int>graph;//глобальный объект класса
Graph <int> makeGraph()
{
	Graph <int> graph; // создание графа, содержащего вершины с номерами целого типа
	int amountVerts, amountEdges, sourceVertex, targetVertex, edgeWeight; // создание необходимых для ввода графа переменных
	cout << "Введите количество вершин графа: "; cin >> amountVerts; cout << endl; // ввод количества рёбер графа в переменную amountVerts
	cout << "Введите количество ребер графа: "; cin >> amountEdges; cout << endl; // ввод количества рёбер графа в переменную amountEdges
	for (int i = 1; i <= amountVerts; ++i) {
		int* vertPtr = &i; // запоминаем адрес вершины с помощью указателя
		graph.InsertVertex(*vertPtr); //передаём ссылку на вершину в функцию InsertVertex; происходит вставка вершины в вектор вершин
	}

	for (int i = 0; i < amountEdges; ++i)
	{
		cout << "Исходная вершина: "; cin >> sourceVertex; cout << endl; // ввод исходной вершины
		int* sourceVertPtr = &sourceVertex; // запоминаем адрес исходной вершины
		cout << "Конечная вершина: "; cin >> targetVertex; cout << endl; // ввод вершины, до которой будет идти ребро от исходной вершины
		int* targetVertPtr = &targetVertex; // запоминаем адрес конечной вершины (до которой будет идти ребро от исходной вершины)

		cout << "Вес ребра: "; cin >> edgeWeight; cout << endl; // ввод числового значения веса ребра в переменную edgeWeight
		graph.InsertEdge(*sourceVertPtr, *targetVertPtr, edgeWeight); // вставка ребра весом edgeWeight между исходной и конечной вершинами
	}
	cout << endl;
	graph.Print();//печать матрицы смежности
	return graph;
}
const int V = 6;
//изображение
void display()
{
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WinW, 0, WinH); //ставим начало координат в левый нижний угол
	glViewport(0, 0, WinW, WinH);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	graph.DrawGraph();
	glutSwapBuffers();
}
 //функция нахождения кратчайшего пути и пути до них
void Komm(int gl[20][20], int st)
{
	int distance[V];//дистанция до искомой вершины
	int count, index, u, m = st + 1;
	int f[6];
	bool visited[6];//переменная отмечает была ли посещена вершина
	int n = 0; f[n] = st; n++;
	cout << "вершина  " << st + 1 << " посещена" << endl;
	for (int i = 0; i < V; i++)
	{
		distance[i] = 1000;//дистанция до вершины принимает максимальный размер
		visited[i] = false;//все вершины не посещены
	}
	distance[st] = 0;//дистанция до исходной вершины равна 0
	for (count = 0; count < V - 1; count++)
	{
		int min = 1000;
		for (int i = 0; i < V; i++)
		{
			if (!visited[i] && distance[i] <= min)
			{
				min = distance[i];
				index = i;
			}
		}
		u = index;
		visited[u] = true;//вершина помечается помещенной
		for (int i = 0; i < V; i++)//добавление длины ребра
		{
			if (!visited[i] && gl[u][i] && distance[u] != 1000 && distance[u] + gl[u][i] < distance[i])
			{
				distance[i] = distance[u] + gl[u][i];
				f[n] = i; n++;
				cout << "Вершина  " << i + 1 << " посещена" << endl;
			}
		}
	}
	for (int i = 0; i<V; i++)
	{
		if (distance[i] != 1000)//вывод дистанции до вершины
		{
			cout << endl;
			cout << "Длина пути от " << m << " до " << i + 1 << " = " << distance[i] << endl;
		}
		else cout << m << " > " << i + 1 << " = " << "маршрут недоступен" << endl;
	}
}

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "rus");
	glutInit(&argc, argv);
	graph = makeGraph();
	int start; cout << "Начальная вершина >> "; cin >> start;
	Komm(graph.adjMatrix, start - 1);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(900, 720);
	glutCreateWindow("Graph");
	WinW = glutGet(GLUT_WINDOW_WIDTH);
	WinH = glutGet(GLUT_WINDOW_HEIGHT);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	_getch();
    return 0;
}