#pragma once
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int maxSize = 20;
vector <int> labelList;
template <class T>
class Graph
{
public:
	Graph();//�����������
	~Graph();//����������
	int adjMatrix[20][20];//������� ���������
	vector <int> vertList;//������ ������ �����
	int GetVertPos(const T&);//��������� ������� �������
	bool IsEmpty();//�������� ����� �� �������
	bool IsFull();//�������� �������� �� ���������� ������ ����� ������������� �������
	int GetAmountVerts();//����� ���������� ���������� ������ � �����
	int GetAmountEdges();//����� ���������� ���������� ����� � �����
	int GetWeight(const T& vertex1, const T& vertex2);//����� ���������� ��� �����
	vector<T> GetNbrs(const T & vertex);//������ ������� �������
	void InsertVertex(const T& vertex);//����� ���������� �������
	void InsertEdge(const T & vertex1, const T & vertex2, int weight);//����� ��������� ����� ����� ����� ���������
	void Print();//����� ������� ���������
	void DrawGraph();//��������� �����
};
//�����������
template<class T>
Graph<T>::Graph()
{
	//������� ����� � �������� ������� ��������� � ���������� � ������
	for (int i = 0; i < maxSize; ++i) {
		for (int j = 0; j < maxSize; ++j) {
			this->adjMatrix[i][j] = 0;
		}
	}
}
//����������
template<class T>
Graph<T>::~Graph()
{
}
//������� ������� ������� � ������� ������
template <class T>
int Graph<T>::GetVertPos(const T& vertex)
{
	for (int i = 0; i < this->vertList.size(); ++i) {
		if (this->vertList[i] == vertex)
			return i;
	}
	return -1;
}
//�������� ���� �� ����
template<class T>
bool Graph<T>::IsEmpty()
{
	if (this->vertList.size() != 0)
		return false;
	else
		return true;
}
//�������� �������� �� ���������� ������ � ����� ����������� ���������� �������
template<class T>
bool Graph<T>::IsFull()
{
	return (vertList.size() == maxSize);
}
//���������� ���������� ������ � �����
template<class T>
int Graph<T>::GetAmountVerts()
{
	return this->vertList.size();
}
//����������� ���������� ����� � �����
template<class T>
int Graph<T>::GetAmountEdges()
{
	int amount = 0; // �������� �������
	if (!this->IsEmpty()) { // ���������, ��� ���� �� ����
		for (int i = 0, vertListSize = this->vertList.size(); i < vertListSize; ++i) {
			for (int j = 0; j < vertListSize; ++j) {
				if (this->adjMatrix[i][j] == 1) // ������� ����
					amount += 1; // ������� ���������� ����
			}
		}
		return amount; // ���������� ���������� ����
	}
	else
		return 0; // ���� ���� ����, ���������� 0
}
//����������� ���� �����, ������������ �����
template<class T>
int Graph<T>::GetWeight(const T & vertex1, const T & vertex2) {
	if (!this->IsEmpty()) {
		int vertPos1 = GetVertPos(vertex1);
		int vertPos2 = GetVertPos(vertex2);
		return adjMatrix[vertPos1][vertPos2];
	}
	return 0;
}
//����� ���������� ������ ������� ������� vertex, ������ �� ������� ����� ���������
template<class T>
vector<T> Graph<T>::GetNbrs(const T & vertex)
{
	std::vector<T> nbrsList; // �������� ������ �������
	int pos = this->GetVertPos(vertex); /* ���������� ������� vertex � ������� ��������� */
	if (pos != (-1)) { /* ��������, ��� vertex ���� � ������� ��������� */
		for (int i = 0, vertListSize = this->vertList.size(); i < vertListSize; ++i) {
			if (this->adjMatrix[pos][i] != 0) /* ���������� �������*/
				nbrsList.push_back(this->vertList[i]); /* ������ ������� � ������ */
		}
	}
	return nbrsList; // ������� ������ �������
}
//���������� �������
template<class T>
void Graph<T>::InsertVertex(const T& vertex) {
	if (!this->IsFull()) {
		this->vertList.push_back(vertex);
	}
	else {
		cout << "���� ��� ��������. ���������� �������� ����� ������� " << endl;
		return;
	}
}
//����� ��������� ����� ��������� vertex1 � vertex2 ����� ����� weight
template<class T>
void Graph<T>::InsertEdge(const T & vertex1, const T & vertex2, int weight) {
	if (this->GetVertPos(vertex1) != (-1) && this->GetVertPos(vertex2) != (-1)) {
		int vertPos1 = GetVertPos(vertex1);
		int vertPos2 = GetVertPos(vertex2);
		if (this->adjMatrix[vertPos1][vertPos2] != 0) {
			cout << "����� ����� ����� ��������� ��� ����������" << endl;
			return;
		}
		else {
			this->adjMatrix[vertPos1][vertPos2] = weight;
		}
	}
	else {
		cout << "����� ������ (��� ����� �� ���) ��� � ����� " << endl;
		return;
	}
}
//���� ����� ������������ ��� ������ ������� ��������� �����
template<class T>
void Graph<T>::Print()
{
	if (!this->IsEmpty()) {
		cout << "������� ��������� �����: " << endl;
		for (int i = 0, vertListSize = this->vertList.size(); i < vertListSize; ++i) {
			cout << this->vertList[i] << " ";
			for (int j = 0; j < vertListSize; ++j) {
				cout << " " << this->adjMatrix[i][j] << " ";
			}
			cout << endl;
		}
	}
	else {
		cout << "���� ���� " << endl;
	}
}