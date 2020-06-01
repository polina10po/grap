#include <glut.h>
#include "Graph.h"
#include <iostream>
#include <conio.h>
#include <locale>
#include <queue>
#include <stack>
#include "Print.h"
using namespace std;

Graph<int>graph;//���������� ������ ������
Graph <int> makeGraph()
{
	Graph <int> graph; // �������� �����, ����������� ������� � �������� ������ ����
	int amountVerts, amountEdges, sourceVertex, targetVertex, edgeWeight; // �������� ����������� ��� ����� ����� ����������
	cout << "������� ���������� ������ �����: "; cin >> amountVerts; cout << endl; // ���� ���������� ���� ����� � ���������� amountVerts
	cout << "������� ���������� ����� �����: "; cin >> amountEdges; cout << endl; // ���� ���������� ���� ����� � ���������� amountEdges
	for (int i = 1; i <= amountVerts; ++i) {
		int* vertPtr = &i; // ���������� ����� ������� � ������� ���������
		graph.InsertVertex(*vertPtr); //������� ������ �� ������� � ������� InsertVertex; ���������� ������� ������� � ������ ������
	}

	for (int i = 0; i < amountEdges; ++i)
	{
		cout << "�������� �������: "; cin >> sourceVertex; cout << endl; // ���� �������� �������
		int* sourceVertPtr = &sourceVertex; // ���������� ����� �������� �������
		cout << "�������� �������: "; cin >> targetVertex; cout << endl; // ���� �������, �� ������� ����� ���� ����� �� �������� �������
		int* targetVertPtr = &targetVertex; // ���������� ����� �������� ������� (�� ������� ����� ���� ����� �� �������� �������)

		cout << "��� �����: "; cin >> edgeWeight; cout << endl; // ���� ��������� �������� ���� ����� � ���������� edgeWeight
		graph.InsertEdge(*sourceVertPtr, *targetVertPtr, edgeWeight); // ������� ����� ����� edgeWeight ����� �������� � �������� ���������
	}
	cout << endl;
	graph.Print();//������ ������� ���������
	return graph;
}
const int V = 6;
//�����������
void display()
{
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WinW, 0, WinH); //������ ������ ��������� � ����� ������ ����
	glViewport(0, 0, WinW, WinH);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	graph.DrawGraph();
	glutSwapBuffers();
}
 //������� ���������� ����������� ���� � ���� �� ���
void Komm(int gl[20][20], int st)
{
	int distance[V];//��������� �� ������� �������
	int count, index, u, m = st + 1;
	int f[6];
	bool visited[6];//���������� �������� ���� �� �������� �������
	int n = 0; f[n] = st; n++;
	cout << "�������  " << st + 1 << " ��������" << endl;
	for (int i = 0; i < V; i++)
	{
		distance[i] = 1000;//��������� �� ������� ��������� ������������ ������
		visited[i] = false;//��� ������� �� ��������
	}
	distance[st] = 0;//��������� �� �������� ������� ����� 0
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
		visited[u] = true;//������� ���������� ����������
		for (int i = 0; i < V; i++)//���������� ����� �����
		{
			if (!visited[i] && gl[u][i] && distance[u] != 1000 && distance[u] + gl[u][i] < distance[i])
			{
				distance[i] = distance[u] + gl[u][i];
				f[n] = i; n++;
				cout << "�������  " << i + 1 << " ��������" << endl;
			}
		}
	}
	for (int i = 0; i<V; i++)
	{
		if (distance[i] != 1000)//����� ��������� �� �������
		{
			cout << endl;
			cout << "����� ���� �� " << m << " �� " << i + 1 << " = " << distance[i] << endl;
		}
		else cout << m << " > " << i + 1 << " = " << "������� ����������" << endl;
	}
}

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "rus");
	glutInit(&argc, argv);
	graph = makeGraph();
	int start; cout << "��������� ������� >> "; cin >> start;
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