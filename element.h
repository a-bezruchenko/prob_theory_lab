#include <list>
#include <string>
#include "canvas.h"

enum Type {TypeParallel, TypeSerial, TypeReal, TypeAbstract};

class abstractElement
{
public:
	abstractElement();
	
	Type getType(); // получить тип; это просто костыль вместо typeOf
	bool operator==(abstractElement& other);

	virtual long double prob_breaks() = 0; // вывести вероятность поломки
	virtual Canvas* getImage() = 0; // получить изображение элемента
	virtual int getName() = 0; // получить имя элемента
	virtual std::string getFormule() = 0; // получить формулу, по которой рассчитывается вероятность поломки схемы
	virtual unsigned getH() = 0; // получить высоту элемента
	virtual unsigned getW() = 0; // получить ширину элемента
protected:
	Type type; // тип элемента
	int id; // номер; конечное имя получается путем приписывания типа элемента
};



class virtualElement: public abstractElement
{
public:
	virtualElement();
	~virtualElement();
	virtualElement(bool isParallel, abstractElement* element);

	long double prob_breaks();
	Canvas* getImage();
	std::string getFormule();
	int getName();
	std::list <std::string> getFullFormule(); // получить полную формулу
	unsigned getH();
	unsigned getW();

	void createParallel(abstractElement* element, abstractElement* addedElement);
	void createSerial(abstractElement* element, abstractElement* addedElement);

protected:
	std::list <abstractElement*> content; // содержимое

	bool isInContent(abstractElement* element); // проверить, есть ли данный элемент внутри

	void addChild(abstractElement* child); // добавить элемент
	void removeChild(abstractElement* child); // удалить элемент
};



class realElement: public abstractElement
{
public:
	realElement(long double prob, int name);
	realElement(long double prob, virtualElement* parent);
	realElement(long double prob);
	realElement();
	realElement(const realElement&);

	realElement& realElement::operator=(const realElement& other);

	long double prob_breaks();
	Canvas* getImage(); 
	std::string getFormule();
	unsigned getH();
	unsigned getW();

	int getName();

	void addParallel(abstractElement *element); // добавить элемент параллельно данному
	void addSerial(abstractElement *element); // добавить элемент последовательно данному

	void setParent(virtualElement* parent);
	void setProb(long double prob);

	virtualElement* getParent();

protected:
	long double prob; // вероятность поломки данного элемента
	int name; // имя элемента
	virtualElement* parent; // указатель на родительский элемент
};