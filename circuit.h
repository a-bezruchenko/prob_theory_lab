#ifndef CIRCIUT_H
#define CIRCIUT_H

#include "element.h"
#include <fstream>
#include <vector>

class Circuit
{
public:
	Circuit();

	void setFirst(); // ���������� ������ �����
	void setSecond(); // ���������� ������ �����
	void setDumb(unsigned int amount); // ������� ������ ����� � �������� ���-��� ���������
	void readFile(char name[]); // ������� ����� �� �����
	
	void setProbs(long double* probs); // ���������� ����������� ������ �� ����� ��������

	void addSerial(int n); // �������� ����� ��. ��������������� � ��-�� � ������� n
	void addParallel(int n); // �������� ����� ��. ����������� � ��-�� � ������� n

	//void saveFile(char name[]); // ��������� ����� � ����
	void print(); // ������� ����� � �������
	std::vector <long double> getProbs(); // �������� ������ ������������ ������� �������� ���������
	std::string getFormule(); // �������� �������, �� ������� ��������� �����������
	std::list <std::string> getFullFormule(); // �������� ������ ����� � ������ ��������

	unsigned getSize();

	long double getProb_breaks(); // ����� ����������� ����, ��� ����� ���������
	//std::string getFormule(); // �������� �������, �� ������� ��� ����������� ���������

protected:
	std::vector<char*> log; // ��� ����������� ��������
	unsigned int size; // ���������� ���������
	virtualElement* root; // ������ ������ ���������

	std::vector <realElement*> elements; // ������ �������� ���������

	void linkParallel(unsigned int i, unsigned int i_linked);
	void linkSerial(unsigned int i, unsigned int i_linked);
	//realElement* elements; // ��������� �� ������ �������� ���������
};

#endif //CIRCIUT_H