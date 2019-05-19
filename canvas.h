#ifndef CANVAS_H
#define CANVAS_H

#include <stdio.h>

class Canvas
{
public:
	Canvas(unsigned int height, unsigned int width); 
	~Canvas();
	// добавить к данному полотну переданное в заданную позицию
	// позволяет игнорировать пробелы или нет
	void add(Canvas* added, unsigned int x, unsigned int y, bool ignoreSpaces = false); 
	void print();

	void setData(unsigned x, unsigned y, char c);
	char getData(unsigned x, unsigned y);

	void drawHLine(char c, unsigned x, unsigned y, unsigned lenght);
	void drawVLine(char c, unsigned x, unsigned y, unsigned lenght);

	void insertString(char* str, unsigned x, unsigned y);

	unsigned int getHeight();
	unsigned int getWidth();
protected:
	char** data; // хранимое изображение
	unsigned int height; // аррр, я не помню, как пишется это слово
	unsigned int width; // ширина рисунка
};

#endif //CANVAS_H