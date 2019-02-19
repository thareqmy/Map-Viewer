#ifndef FRAME_H_
#define FRAME_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "Point.h"
#include "Color.h"
#include "Pixel.h"
#include "Line.h"
#include "Plane2D.h"

#define XMAX 1300
#define YMAX 700
#define XMIN 25
#define YMIN 25

//Frame Data Structure
class Frame {
public:
	//Frame for  device
	int fbfd;

	//Variable information in device
	struct fb_var_screeninfo vinfo;

	//frame information in device
	struct fb_fix_screeninfo finfo;
	
	//Frame size
	long long screensize;

	
	//Where the pixel information mapped
	char* fbp;


	Frame();
	long long getLocationOnFrame(int x, int y);	
	long long getLocationOnFrame(Point p);
	void createBackground(Color c);
	void inputFBP(long long loc, Color c);
	void pixelToFrame(Pixel);
	void lineToFrame(Color, Line);
	Pixel getPixelFromLoc(int x, int y);
	bool isPixelOccupied(int x, int y, Color occupiedColor);
	void plane2DToFrame(int offsetx, int offsety, int multiplier, Color c, Plane2D pl);

	//Pixel FBPToPixel(Point);
	//Pixel FBPToPixel(int x,int y);


};


#endif