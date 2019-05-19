#include "element.h"

/////////////////////////////////
// realElement
/////////////////////////////////

static int lastId = 0;

realElement::realElement(long double prob, int name)
{
	this->prob = prob;
	this->parent = 0;
	this->type = TypeReal;
	this->name = name;
	id = lastId;
	lastId++;
}

realElement::realElement(long double prob, virtualElement* parent)
{
	this->prob = prob;
	this->parent = parent;
	this->type = TypeReal;
	name = 0;
	id = lastId;
	lastId++;
}

realElement::realElement(long double prob)
{
	this->prob = prob;
	this->parent = 0;
	this->type = TypeReal;
	name = 0;
	id = lastId;
	lastId++;
}

realElement::realElement()
{
	this->prob = 0;
	this->parent = 0;
	this->type = TypeReal;
	name = 0;
	id = lastId;
	lastId++;
}

realElement& realElement::operator=(const realElement& other)
{
	this->id = other.id;
	this->name = other.name;
	this->parent = other.parent;
	this->type = other.type;
	this->prob = other.prob;

	return *this;
}

realElement::realElement(const realElement& other)
{
	*this = other;
}


long double realElement::prob_breaks()
{
	return prob;
}

int realElement::getName()
{
	if (name)	return name;
	else		return id;
}

void realElement::setParent(virtualElement* parent)
{
	this->parent = parent;
}

void realElement::setProb(long double prob)
{
	this->prob = prob;
}

virtualElement* realElement::getParent()
{
	return parent;
}


void realElement::addParallel(abstractElement *element)
{
	parent->createParallel(this, element);
}


void realElement::addSerial(abstractElement *element)
{
	parent->createSerial(this, element);
}


/*
 |------|
-|  12  |-
 |------|
*/
Canvas* realElement::getImage()
{
	Canvas *temp= new Canvas(3, 10);
	temp->drawVLine('|', 1, 0, 3);
	temp->drawVLine('|', 8, 0, 3);
	temp->drawHLine('-', 2, 0, 6);
	temp->drawHLine('-', 2, 2, 6);
	temp->setData(0, 1, '-');
	temp->setData(9, 1, '-');
	char buf[256];
	sprintf(buf, "%d", getName());
	temp->insertString(buf, 4, 1);
	return temp;
}

std::string realElement::getFormule()
{
	char buf[256];
	sprintf(buf, "q%d", getName());
	return std::string(buf);
}

unsigned realElement::getH()
{
	return 3;
}

unsigned realElement::getW()
{
	return 10;
}