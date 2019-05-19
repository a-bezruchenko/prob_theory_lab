#include "canvas.h"

Canvas::Canvas(unsigned int height, unsigned int width)
{

	this->height = height;
	this->width = width;

	data = new char*[height];
	//data = new char*[width];
	for (int row = 0; row < height; row++)
	{
		data[row] = new char[width];
		for (int col = 0; col < width; col++)
			data[row][col] = ' ';
	}
}

Canvas::~Canvas() // в рот мне ноги, неужели я в кой-то веки не поленился сделать деструктор?
{
	for (int i = 0; i < height; i++)
		delete data[i];

	delete data;
}

unsigned int Canvas::getHeight()
{
	return height;
}

unsigned int Canvas::getWidth()
{
	return width;
}

void Canvas::add(Canvas* added, unsigned int x, unsigned int y, bool ignoreSpaces)
{
	for (int row = 0; row < added->getHeight() && row+y < getHeight(); row++)
		for (int col = 0; col < added->getWidth() && col+x < getWidth(); col++)
			setData(col+x, row+y, added->getData(col, row));


		/*
	for (int i = y; i < y+added->getHeight() && i < getHeight(); i++)
		for (int j = x; j < x+added->getWidth() && j < getWidth(); j++)
			if (!ignoreSpaces || added->getData(j, i)!=' ')
				setData(j, i, added->getData(j, i));*/
}

void Canvas::setData(unsigned x, unsigned y, char c)
{
	if (x < width && y < height)
		data[y][x] = c;
}

char Canvas::getData(unsigned x, unsigned y)
{
	if (x < width && y < height)
		return data[y][x];
	else
		return '#';
}

void Canvas::print()
{
	printf("============================================\n");
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
			printf("%c", getData(col, row));

		printf("\n");
	}
	printf("============================================\n");
}


void Canvas::drawHLine(char c, unsigned x, unsigned y, unsigned lenght)
{	
	for (int i = x; i < x+lenght; i++)
		setData(i, y, c);
}


void Canvas::drawVLine(char c, unsigned x, unsigned y, unsigned lenght)
{
	for (int i = y; i < y+lenght; i++)
		setData(x, i, c);
}

void Canvas::insertString(char* str, unsigned x, unsigned y)
{
	for (int i = 0; str[i] && x+i < width; i++)
		setData(x+i, y, str[i]);
}

