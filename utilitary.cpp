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
			printf("Введите q[%d]: ", i+1);
			scanf("%s", buf);

			// если есть точка, заменяем на запятую
			char* temp = strchr(buf, '.');
			if (temp) *temp = ',';
			sscanf(buf, "%Lf", &temp_num);

			if (temp_num < 0 || temp_num > 1) printf("Недопустимое значение\n");
			else targetArr[i] = temp_num;
		}
	}
}

void printHelp()
{
	printf("\nДопустимые команды: (в скобках указаны другие варианты той же команды)\n");
	printf("help - просмотреть справку по основным командам\n");
	printf("fullhelp - просмотреть справку со всеми командами\n");
	printf("exit - выйти из программы\n");
	printf("clear - очистить экран\n");
	printf("load1 - загрузить первую схему\n");
	printf("load2 - загрузить вторую схему\n");
	printf("view (print) - просмотреть загруженную схему\n");
	printf("formule - распечатать формулу, по которой будет считаться вероятность выхода схемы из строя\n");
	printf("fullformule - распечатать формулу для расчета вероятности выхода из строя каждой ветви\n");
	printf("test – ввести вероятности выхода из строя элементов и рассчитать вероятность выхода всей схемы из строя\n");
}

void printEditHelp()
{
	printf("\nhelp - распечатать справку по режиму редактирования\n");
	printf("stop - выйти из этого режима\n");
	printf("new (delete) - сбросить схему\n");
	printf("p (par, parallel) – присоединить параллельно\n");
	printf("s (ser, serial) – присоединить последовательно\n");
	printf("После ввода команд p и s вводится одно число – номер элемента\n");
	printf("К элементу с этим номером присоединяется новый\n");
}

void printFullHelp()
{
	printHelp();
	printf("set - установить вероятности выхода из строя элементов\n");
	printf("probs (values) – просмотреть ранее установленные вероятности\n");
	printf("calc - рассчитать вероятность выхода заданной схемы из строя\n");
	printf("edit - перейти в режим редактирования\n");
	printf("\nКоманды режима редактирования:\n");
	printEditHelp();
}
