#include <list>
#include <string>
#include "canvas.h"

enum Type {TypeParallel, TypeSerial, TypeReal, TypeAbstract};

class abstractElement
{
public:
	abstractElement();
	
	Type getType(); // �������� ���; ��� ������ ������� ������ typeOf
	bool operator==(abstractElement& other);

	virtual long double prob_breaks() = 0; // ������� ����������� �������
	virtual Canvas* getImage() = 0; // �������� ����������� ��������
	virtual int getName() = 0; // �������� ��� ��������
	virtual std::string getFormule() = 0; // �������� �������, �� ������� �������������� ����������� ������� �����
	virtual unsigned getH() = 0; // �������� ������ ��������
	virtual unsigned getW() = 0; // �������� ������ ��������
protected:
	Type type; // ��� ��������
	int id; // �����; �������� ��� ���������� ����� ������������ ���� ��������
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
	std::list <std::string> getFullFormule(); // �������� ������ �������
	unsigned getH();
	unsigned getW();

	void createParallel(abstractElement* element, abstractElement* addedElement);
	void createSerial(abstractElement* element, abstractElement* addedElement);

protected:
	std::list <abstractElement*> content; // ����������

	bool isInContent(abstractElement* element); // ���������, ���� �� ������ ������� ������

	void addChild(abstractElement* child); // �������� �������
	void removeChild(abstractElement* child); // ������� �������
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

	void addParallel(abstractElement *element); // �������� ������� ����������� �������
	void addSerial(abstractElement *element); // �������� ������� ��������������� �������

	void setParent(virtualElement* parent);
	void setProb(long double prob);

	virtualElement* getParent();

protected:
	long double prob; // ����������� ������� ������� ��������
	int name; // ��� ��������
	virtualElement* parent; // ��������� �� ������������ �������
};