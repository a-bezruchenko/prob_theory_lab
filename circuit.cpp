#include "circuit.h"

Circuit::Circuit()
{
	log.clear();
	elements.clear();
	elements.push_back(new realElement(1, 1));

	size = 1;

	root = new virtualElement(false, elements[0]);
}


void Circuit::setDumb(unsigned int amount)
{
	if (amount > 0)
	{
		log.clear();
		
		elements.clear();
		delete root;

		elements.reserve(amount);

		for (int i = 0; i < amount; i++)
			elements.push_back(new realElement(0, i+1));
		
		size = amount;

		root = new virtualElement(false, elements[0]);
	}
}

void Circuit::setFirst()
{
	setDumb(6);
	
	elements[0]->addSerial		(elements[1]);
	elements[1]->addParallel	(elements[4]);
	elements[1]->addSerial		(elements[2]);
	elements[2]->addParallel	(elements[3]);
	elements[4]->addSerial		(elements[5]);
}

void Circuit::setSecond()
{
	setDumb(7);

	elements[0]->addSerial		(elements[5]);
	elements[5]->addParallel	(elements[1]);
	elements[5]->addParallel	(elements[6]);
	elements[1]->addSerial		(elements[4]);
	elements[1]->addParallel	(elements[2]);
	elements[1]->addParallel	(elements[3]);
	
}

void Circuit::setProbs(long double* probs)
{
	for (int i = 0; i < size; i++)
		elements[i]->setProb(probs[i]);
}

long double Circuit::getProb_breaks()
{
	return root->prob_breaks();
}

void Circuit::addSerial(int n)
{
	if (n <= size)
	{
		elements.push_back(new realElement(0, size+1));
		size++;
		linkSerial(n, size);
	}
	print();
}

void Circuit::addParallel(int n)
{
	if (n <= size)
	{
		elements.push_back(new realElement(1, size+1));
		size++;
		linkParallel(n, size);
	}
	print();
}


void Circuit::linkParallel(unsigned int i, unsigned int i_linked)
{
	elements[i-1]->addParallel(elements[i_linked-1]);
	char buf[256];
	sprintf(buf, "p %d %d", i-1, i_linked-1);
	log.push_back(buf);
}

void Circuit::linkSerial(unsigned int i, unsigned int i_linked)
{
	elements[i-1]->addSerial(elements[i_linked-1]);
	char buf[256];
	sprintf(buf, "s %d %d", i-1, i_linked-1);
	log.push_back(buf);
}


void Circuit::print()
{

	Canvas* image = root->getImage();
	Canvas* result = new Canvas(image->getHeight(), image->getWidth()+10);
	result->add(image, 4, 0);
	result->setData(3, image->getHeight()/2, 'O');
	result->setData(result->getWidth()-6, image->getHeight()/2, 'O');
	delete image;
	result->print();
	delete result;
}

unsigned Circuit::getSize()
{
	return size;
}

std::vector <long double> Circuit::getProbs()
{
	std::vector <long double> result;
	for (auto i = elements.begin(); i!= elements.end(); i++)
		result.push_back((*i)->prob_breaks());
	return result;
}

std::string Circuit::getFormule()
{
	return root->getFormule();
}

/*

	char buf[256];
	int amount;
	std::string buf_out;
	std::vector <std::string> log;

	
	ifstream fin("test.txt");
	fin.getline(buf, 50);

	sscanf(buf, "%d", &amount);

	for (int i = 0; i< amount; i++)
	{
		fin.getline(buf, 256);
		log.push_back(string(buf));
	}
	fin.close();

	amount++;
	log.push_back(string("s 1 2"));

	itoa(amount, buf, 10);

	ofstream fout("test.txt"); 

	fout << buf;

	for (std::vector<std::string>::iterator i = log.begin(); i!= log.end(); i++)
		fout << endl << *i;

    
    fout << buf_out; 
    fout.close();
*/

std::list <std::string> Circuit::getFullFormule()
{
	std::list <std::string> buf;
	std::string temp;
	char num[234];
	temp += "S";
	sprintf(num, "%d", root->getName());
	temp += num;
	temp += " - вся схема";
	buf.push_back(temp);
	buf.push_back("e - элементы схемы, для которых устанавливается вероятность выхода из строя");
	buf.push_back("S - последовательный участок схемы");
	buf.push_back("П - параллельный участок схемы");
	buf.splice(buf.end(), root->getFullFormule());
	return buf;
}