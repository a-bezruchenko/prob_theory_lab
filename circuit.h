#ifndef CIRCIUT_H
#define CIRCIUT_H

#include "element.h"
#include <fstream>
#include <vector>

class Circuit
{
public:
	Circuit();

	void setFirst(); // установить первую схему
	void setSecond(); // установить вторую схему
	void setDumb(unsigned int amount); // создать пустую схему с заданным кол-вом элементов
	void readFile(char name[]); // считать схему из файла
	
	void setProbs(long double* probs); // установить вероятность выхода из строя элемента

	void addSerial(int n); // добавить новый эл. последовательно с эл-ом с номером n
	void addParallel(int n); // добавить новый эл. параллельно с эл-ом с номером n

	//void saveFile(char name[]); // сохранить схему в файл
	void print(); // вывести схему в консоль
	std::vector <long double> getProbs(); // получить вектор вероятностей поломки реальных элементов
	std::string getFormule(); // получить формулу, по которой считается вероятность
	std::list <std::string> getFullFormule(); // получить массив строк с полной формулой

	unsigned getSize();

	long double getProb_breaks(); // найти вероятность того, что схема сломается
	//std::string getFormule(); // получить формулу, по которой эта вероятность считается

protected:
	std::vector<char*> log; // лог выполненных операций
	unsigned int size; // количество элементов
	virtualElement* root; // корень дерева элементов

	std::vector <realElement*> elements; // вектор реальных элементов

	void linkParallel(unsigned int i, unsigned int i_linked);
	void linkSerial(unsigned int i, unsigned int i_linked);
	//realElement* elements; // указатель на массив реальных элементов
};

#endif //CIRCIUT_H