#ifndef LINE_H_
#define LINE_H_
#include "Point.h"

//Pixel Data Structure
class Line {
public:
	//ATR
	Point p1;
	Point p2;
	//CONS

	//CREATE CONS USING POINT
	Line();
	Line(Point p1, Point p2);
	//CREATE CONS USING 4 INT as Point
	Line(int x1, int y1, int x2, int y2);

	//METHOD
	double getGradient();

	//convert line to points using bresenham
	Point* getArrayOfPoints(int* N);

};

#endif