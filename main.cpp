#include "utilitary.h"
#include "circuit.h"

enum Mode {ModeView, ModeEdit};

int main()
{
	setlocale(LC_ALL, "Russian");

	bool HALT = false;
	bool wasInEditMode = false;
	int mode = ModeView;
	std::string buf;
	unsigned num_buf;
	Circuit circuit;

	printHelp();

	while (!HALT)
	{
		std::cout << ">";
		std::getline(std::cin, buf);

		if (mode == ModeView)
		{
			if (buf == "help")			
				printHelp();
			else if (buf == "fullhelp")
				printFullHelp();
			else if (buf == "exit")		
				HALT = true;
			else if (buf == "clear")
				system("cls");
			else if (buf == "load1")	
			{
				circuit.setFirst();
				printf("Схема загружена\n");
			}
			else if (buf == "load2")	
			{
				circuit.setSecond();
				printf("Схема загружена\n");
			}
			else if (buf == "set")
			{
				long double *values = new long double [circuit.getSize()];
				readMultipleProbs(values, circuit.getSize());
				circuit.setProbs(values);
				delete values;
				std::getline(std::cin, buf);
			}
			else if (buf == "calc")		
				printf("Вероятность выхода схемы из строя: %Lf\n", circuit.getProb_breaks());
			else if (buf == "formule")
				std::cout << circuit.getFormule() << std::endl;
			else if (buf == "fullformule")
			{
				auto buf = circuit.getFullFormule();
				for (auto i = buf.begin(); i != buf.end(); i++)
					std::cout << *i << std::endl;
			}
			else if (buf == "test")
			{
				long double *values = new long double [circuit.getSize()];
				readMultipleProbs(values, circuit.getSize());
				circuit.setProbs(values);
				delete values;
				std::getline(std::cin, buf);
				printf("Вероятность выхода схемы из строя: %Lf\n", circuit.getProb_breaks());
			}
			else if (buf == "view" || buf == "print")		
				circuit.print();
			else if (buf == "probs" || buf == "values") 
			{
				auto p_vec = circuit.getProbs();
				int n = 1;
				for (auto i = p_vec.begin(); i != p_vec.end(); i++, n++)
					printf("q[%d]: %Lf\n", n , *i);
			}
			else if (buf == "edit")		
			{
				mode = ModeEdit;
				if (!wasInEditMode)
				{
					wasInEditMode = true;
					printEditHelp();
				}
			}
			else						
				printf("Неизвестная команда\n");
		}
		else 
		{

			if (buf == "help")
				printEditHelp();
			else if (buf == "new" || buf == "delete")
			{
				circuit.setDumb(1);
				printf("Схема удалена\n");
			}
			else if (buf == "p" || buf == "par" || buf == "parallel")
			{
				scanf("%u", &num_buf);
				circuit.addParallel(num_buf);
			}
			else if (buf == "s" || buf == "ser" || buf == "serial")
			{
				scanf("%u", &num_buf);
				circuit.addSerial(num_buf);
			}
			else if (buf == "stop")	
				mode = ModeView;
			else					
				printf("Неизвестная команда\n");
		}
	}

	return 0;
}