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
	Graph();//Конструктор
	~Graph();//деструктор
	int adjMatrix[20][20];//Матрица смежности
	vector <int> vertList;//вектор вершин графа
	int GetVertPos(const T&);//получение позиции вершины
	bool IsEmpty();//проверка графа на пустоту
	bool IsFull();//проверка достигло ли количество вершин графа максимального предела
	int GetAmountVerts();//метод возвращает количество вершин в графе
	int GetAmountEdges();//метод возвращает количество ребер в графе
	int GetWeight(const T& vertex1, const T& vertex2);//метод возвращает вес ребра
	vector<T> GetNbrs(const T & vertex);//вектор соседей вершины
	void InsertVertex(const T& vertex);//метод добавления вершины
	void InsertEdge(const T & vertex1, const T & vertex2, int weight);//метод вставляет ребро между двумя вершинами
	void Print();//Вывод матрицы смежности
	void DrawGraph();//Рисование графа
};
//конструктор
template<class T>
Graph<T>::Graph()
{
	//перебор строк и столбцов матрицы смежности и заполнение её нулями
	for (int i = 0; i < maxSize; ++i) {
		for (int j = 0; j < maxSize; ++j) {
			this->adjMatrix[i][j] = 0;
		}
	}
}
//деструктор
template<class T>
Graph<T>::~Graph()
{
}
//находит позицию вершины в векторе вершин
template <class T>
int Graph<T>::GetVertPos(const T& vertex)
{
	for (int i = 0; i < this->vertList.size(); ++i) {
		if (this->vertList[i] == vertex)
			return i;
	}
	return -1;
}
//проверка пуст ли граф
template<class T>
bool Graph<T>::IsEmpty()
{
	if (this->vertList.size() != 0)
		return false;
	else
		return true;
}
//проверка достигло ли количество вершин в графе максимально возможного предела
template<class T>
bool Graph<T>::IsFull()
{
	return (vertList.size() == maxSize);
}
//возвращает количество вершин в графе
template<class T>
int Graph<T>::GetAmountVerts()
{
	return this->vertList.size();
}
//возвращение количечтва ребер в графе
template<class T>
int Graph<T>::GetAmountEdges()
{
	int amount = 0; // обнуляем счетчик
	if (!this->IsEmpty()) { // проверяем, что граф не пуст
		for (int i = 0, vertListSize = this->vertList.size(); i < vertListSize; ++i) {
			for (int j = 0; j < vertListSize; ++j) {
				if (this->adjMatrix[i][j] == 1) // находим рёбра
					amount += 1; // считаем количество рёбер
			}
		}
		return amount; // возвращаем количество рёбер
	}
	else
		return 0; // если граф пуст, возвращаем 0
}
//возвращение веса ребра, соединяющего ребра
template<class T>
int Graph<T>::GetWeight(const T & vertex1, const T & vertex2) {
	if (!this->IsEmpty()) {
		int vertPos1 = GetVertPos(vertex1);
		int vertPos2 = GetVertPos(vertex2);
		return adjMatrix[vertPos1][vertPos2];
	}
	return 0;
}
//Метод возвращает список соседей вершины vertex, ссылку на которую метод принимает
template<class T>
vector<T> Graph<T>::GetNbrs(const T & vertex)
{
	std::vector<T> nbrsList; // создание списка соседей
	int pos = this->GetVertPos(vertex); /* вычисление позиции vertex в матрице смежности */
	if (pos != (-1)) { /* проверка, что vertex есть в матрице смежности */
		for (int i = 0, vertListSize = this->vertList.size(); i < vertListSize; ++i) {
			if (this->adjMatrix[pos][i] != 0) /* вычисление соседей*/
				nbrsList.push_back(this->vertList[i]); /* запись соседей в вектор */
		}
	}
	return nbrsList; // возврат списка соседей
}
//добавление вершины
template<class T>
void Graph<T>::InsertVertex(const T& vertex) {
	if (!this->IsFull()) {
		this->vertList.push_back(vertex);
	}
	else {
		cout << "Граф уже заполнен. Невозможно добавить новую вершину " << endl;
		return;
	}
}
//Метод вставляет между вершинами vertex1 и vertex2 ребро весом weight
template<class T>
void Graph<T>::InsertEdge(const T & vertex1, const T & vertex2, int weight) {
	if (this->GetVertPos(vertex1) != (-1) && this->GetVertPos(vertex2) != (-1)) {
		int vertPos1 = GetVertPos(vertex1);
		int vertPos2 = GetVertPos(vertex2);
		if (this->adjMatrix[vertPos1][vertPos2] != 0) {
			cout << "Ребро между этими вершинами уже существует" << endl;
			return;
		}
		else {
			this->adjMatrix[vertPos1][vertPos2] = weight;
		}
	}
	else {
		cout << "Обеих вершин (или одной из них) нет в графе " << endl;
		return;
	}
}
//Этот метод используется для печати матрицы смежности графа
template<class T>
void Graph<T>::Print()
{
	if (!this->IsEmpty()) {
		cout << "Матрица смежности графа: " << endl;
		for (int i = 0, vertListSize = this->vertList.size(); i < vertListSize; ++i) {
			cout << this->vertList[i] << " ";
			for (int j = 0; j < vertListSize; ++j) {
				cout << " " << this->adjMatrix[i][j] << " ";
			}
			cout << endl;
		}
	}
	else {
		cout << "Граф пуст " << endl;
	}
}