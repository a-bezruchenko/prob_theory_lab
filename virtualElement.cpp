#include "element.h"

/////////////////////////////////
// virtualElement
/////////////////////////////////

static int lastId = 0;

virtualElement::virtualElement(bool isParallel, abstractElement* element)
{
	if (isParallel)	
		type = TypeParallel;
	else			
		type = TypeSerial;

	id = lastId;
	addChild(element);
	lastId++;
}

virtualElement::virtualElement()
{}

virtualElement::~virtualElement() // не уверен, что это делается так, но ладно
{
	for (auto i = content.begin(); i != content.end(); i++)
		delete *i;
}

long double virtualElement::prob_breaks()
{
	long double product = 1;
	if (type == TypeParallel) // перемножаем вероятности поломок
	{
		for (auto i = content.begin(); i != content.end(); i++)
			product *= (*(*i)).prob_breaks();

		return product;
	}
	else // перемножаем вероятности работоспособности и вычитаем из единицы
	{
		for (auto i = content.begin(); i != content.end(); i++)
			product *= 1-(*(*i)).prob_breaks();

		return 1-product;
	}
}


void virtualElement::createParallel(abstractElement* element, abstractElement* addedElement)
{
	if (this->type == TypeParallel)
		addChild(addedElement);
	else if (!isInContent(element))
		return;
	else
	{
		virtualElement* replacement = new virtualElement(true, addedElement);
		removeChild(element);
		replacement->addChild(element);
		addChild(replacement);
	}
}

void virtualElement::createSerial(abstractElement* element, abstractElement* addedElement)
{
	if (type == TypeSerial)
		addChild(addedElement);
	else if (!isInContent(element))
		return;
	else
	{
		virtualElement* replacement = new virtualElement(false, addedElement);
		removeChild(element);
		replacement->addChild(element);
		addChild(replacement);
	}
}

bool virtualElement::isInContent(abstractElement* element)
{
	bool isInContent = false;
	for (auto i = content.begin(); i != content.end(); i++)
	{
		if ((*(*i))==(*element))
		{
			isInContent = true;
			break;
		}
	}

	return isInContent;
}

void virtualElement::addChild(abstractElement* child)
{
	content.push_back(child);
	if (child->getType() == TypeReal)
		((realElement*)child)->setParent(this);
}

void virtualElement::removeChild(abstractElement* child)
{
	content.remove(child);
	if (child->getType() == TypeReal)
		((realElement*)child)->setParent(0);
}

Canvas* virtualElement::getImage()
{
	Canvas* image = new Canvas(getH(), getW());
	Canvas* temp_image;

	if (type == TypeSerial)
	{
		// последовательно отрисовать все элементы
		unsigned cur_x = 0;
		unsigned temp_y;
		for (auto i = content.begin(); i != content.end(); i++)
		{
			// вычислить, куда вставить
			temp_image = (*i)->getImage();

			temp_y = (image->getHeight()/2)-(temp_image->getHeight()/2);
			
			// вставить
			image->add(temp_image, cur_x, temp_y);

			// передвинуть курсор
			cur_x += temp_image->getWidth();

			// удаляем промежуточное изображение
			delete temp_image;
			

		}
	}
	else if (type == TypeParallel)
	{
		// нарисовать линии по бокам, затем отрисовать все элементы параллельно
		// между элементами есть пропуск в одну строку
		// не забыть выровнять все элементы по ширине
		unsigned cur_y = 0;
		unsigned line_start = (*content.begin())->getH()/2;
		unsigned line_end;
		for (auto i = content.begin(); i != content.end(); i++)
		{
			// получаем прибавляемое изображение
			temp_image = (*i)->getImage();
			// прибавляем его к общему холсту
			image->add(temp_image, 2, cur_y);
			// вычисляем конец линии для обозначение параллельных элементов
			line_end = cur_y + (temp_image->getHeight())/2;
			// выравниваем отрисованный элемент по ширине, если нужно
			image->drawHLine('-', temp_image->getWidth()+2 , line_end, image->getWidth()-temp_image->getWidth()-4);
			// переходим к следующему элементу 
			cur_y += temp_image->getHeight() + 1;
			// удаляем промежуточное изображение
			delete temp_image;

		}
		image->drawVLine('|', 1, line_start, line_end - line_start + 1);
		image->drawVLine('|', image->getWidth()-2, line_start, line_end - line_start + 1);

		image->setData(0,(image->getHeight()/2),'-');
		image->setData(image->getWidth()-1,(image->getHeight()/2),'-');
		// отрисовать соединительную линию
	}

	return image;
}

std::string virtualElement::getFormule()
{
	std::string result;
	auto i = content.begin();

	result += '(';

	if (type == TypeParallel)
	{
		result += (*i)->getFormule();
		i++;
		for ( ;i != content.end(); i++)
			result += "*" + (*i)->getFormule();
	}
	else
	{
		result += "1-";
		result += "(1-" + (*i)->getFormule() + ")";
		i++;
		for ( ;i != content.end(); i++)
			result += "*(1-" + (*i)->getFormule() + ")";
	}
	result += ')';
	return result;
}

std::list <std::string> virtualElement::getFullFormule()
{
	std::list <std::string> result;
	char buf[256];
	char type;
	//sprintf(buf, "%d", getName());
	//result.push_back(buf);

	if (getType() == TypeSerial)
		type = 'S';
	else
		type = 'П';

	sprintf(buf, "Формула вероятности выхода участка %c%d из строя:", type,  getName());
	result.push_back(buf);
	result.push_back(getFormule());

	sprintf(buf, "Элемент %c%d состоит из: ", type, getName());
	result.push_back(buf);

	for (auto i = content.begin(); i != content.end(); i++)
	{
		if ((*i)->getType() == TypeReal)
			type = 'e';
		else if ((*i)->getType() == TypeSerial)
			type = 'S';
		else
			type = 'П';

		sprintf(buf, "%c%d", type, (*i)->getName());
		result.push_back(buf);
	}




	for (auto i = content.begin(); i != content.end(); i++)
	{
		if ((*i)->getType() == TypeSerial || (*i)->getType() == TypeParallel)
			result.splice(result.end(), ((virtualElement*)(*i))->getFullFormule());
	}
	return result;
}

unsigned virtualElement::getH()
{
	if (type == TypeSerial)
	{
		unsigned max = 0;
		for (auto i = content.begin(); i!=content.end(); i++)
			if ((*i)->getH() > max)
				max = (*i)->getH();

		return max;
	}
	else if (type == TypeParallel)
	{
		unsigned sum = 0;
		for (auto i = content.begin(); i!=content.end(); i++)
			sum += (*i)->getH();
		
		return sum + content.size() - 1;;
	}
	else
	{
		return 0;
	}
}

unsigned virtualElement::getW()
{
	if (type == TypeSerial)
	{
		unsigned sum = 0;
		for (auto i = content.begin(); i!=content.end(); i++)
			sum += (*i)->getW();
		return sum;
	}
	else if (type == TypeParallel)
	{
		unsigned max = 0;
		for (auto i = content.begin(); i!=content.end(); i++)
			if ((*i)->getW() > max)
				max = (*i)->getW();

		return max+4;
	}
	else
	{
		return 0;
	}
}

int virtualElement::getName()
{
	return id;
}