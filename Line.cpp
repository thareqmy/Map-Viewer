#include "Line.h"
#include "Point.h"
#include <algorithm>
#include <iostream>     // std::cout
#include <stdio.h>
#include <math.h>

using namespace std;

//CREATE CONS USING POINT
Line::Line() {
	p1.x = 0;
	p2.x = 0;
	p1.y = 0;
	p2.y = 0;
}

Line::Line(Point p1, Point p2) {
	this->p1 = p1;
	this->p2 = p2;
}

//CREATE CONS USING 4 INT as Point
Line::Line(int x1, int y1, int x2, int y2){
	Point a(x1, y1);
	Point b(x2, y2);
	p1 = a;
	p2 = b;
}

	//METHOD
double Line::getGradient() {
	if (p2.x- p1.x==0){
		return 999;
	}
	double m = (p2.y-p1.y) / (p2.x- p1.x);
	return m;
}

	//convert line to points using bresenham
Point* Line::getArrayOfPoints(int* N) {
  (*N) = 0;
  float x1=p1.x;
  float x2=p2.x;
  float y1=p1.y;
  float y2=p2.y;
  const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
  if(steep)
  {
    swap(x1, y1);
    swap(x2, y2);
  }
 
  if(x1 > x2)
  {
    swap(x1, x2);
    swap(y1, y2);
  }
 
  const float dx = x2 - x1;
  const float dy = fabs(y2 - y1);
 
  float error = dx / 2.0f;
  const int ystep = (y1 < y2) ? 1 : -1;
  int yy = (int)y1;
 
  const int maxX = (int)x2;

  static Point *ptr;
  ptr = new Point[(int)maxX - (int)x1 + 1];
  int i=0;
 
  for(int xx=(int)x1; xx<=maxX; xx++)
  {
    if(steep)
    {
		Point a(yy,xx);
		ptr[i].x = a.x;
		ptr[i].y = a.y;
    }
    else
    {
		Point a(xx,yy);
		ptr[i].x = a.x;
		ptr[i].y = a.y;
    }
    error -= dy;
    if(error < 0)
    {
        yy += ystep;
        error += dx;
    }
	i++;
	(*N)++;
  }
	return ptr;
}
