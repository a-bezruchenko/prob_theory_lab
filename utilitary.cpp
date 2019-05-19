#include "utilitary.h"

void readMultipleProbs(long double *targetArr, unsigned int amount)
{
	long double temp_num;
	char buf [256];

	for (unsigned int i = 0; i < amount; i++)
	{
		temp_num = -1;
		while (temp_num < 0 || temp_num > 1)
		{
			printf("������� q[%d]: ", i+1);
			scanf("%s", buf);

			// ���� ���� �����, �������� �� �������
			char* temp = strchr(buf, '.');
			if (temp) *temp = ',';
			sscanf(buf, "%Lf", &temp_num);

			if (temp_num < 0 || temp_num > 1) printf("������������ ��������\n");
			else targetArr[i] = temp_num;
		}
	}
}

void printHelp()
{
	printf("\n���������� �������: (� ������� ������� ������ �������� ��� �� �������)\n");
	printf("help - ����������� ������� �� �������� ��������\n");
	printf("fullhelp - ����������� ������� �� ����� ���������\n");
	printf("exit - ����� �� ���������\n");
	printf("clear - �������� �����\n");
	printf("load1 - ��������� ������ �����\n");
	printf("load2 - ��������� ������ �����\n");
	printf("view (print) - ����������� ����������� �����\n");
	printf("formule - ����������� �������, �� ������� ����� ��������� ����������� ������ ����� �� �����\n");
	printf("fullformule - ����������� ������� ��� ������� ����������� ������ �� ����� ������ �����\n");
	printf("test � ������ ����������� ������ �� ����� ��������� � ���������� ����������� ������ ���� ����� �� �����\n");
}

void printEditHelp()
{
	printf("\nhelp - ����������� ������� �� ������ ��������������\n");
	printf("stop - ����� �� ����� ������\n");
	printf("new (delete) - �������� �����\n");
	printf("p (par, parallel) � ������������ �����������\n");
	printf("s (ser, serial) � ������������ ���������������\n");
	printf("����� ����� ������ p � s �������� ���� ����� � ����� ��������\n");
	printf("� �������� � ���� ������� �������������� �����\n");
}

void printFullHelp()
{
	printHelp();
	printf("set - ���������� ����������� ������ �� ����� ���������\n");
	printf("probs (values) � ����������� ����� ������������� �����������\n");
	printf("calc - ���������� ����������� ������ �������� ����� �� �����\n");
	printf("edit - ������� � ����� ��������������\n");
	printf("\n������� ������ ��������������:\n");
	printEditHelp();
}
