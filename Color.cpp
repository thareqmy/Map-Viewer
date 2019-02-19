#include <stdlib.h>
#include <stdio.h>
#include "Color.h"

Color::Color(int r, int g, int b) {
	this->r = r;
	this->g = g;
	this->b = b;
}

Color::Color() {

	r = rand() % 255;
	b = rand() % 255;
	g = rand() % 255;

}