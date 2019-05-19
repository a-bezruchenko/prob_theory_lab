#include "element.h"

/////////////////////////////////
// abstractElement
/////////////////////////////////

abstractElement::abstractElement()
{
	this->type = TypeAbstract;
}

bool abstractElement::operator==(abstractElement& other)
{
	return type == other.type && id == other.id;
}

Type abstractElement::getType()
{
	return type;
}