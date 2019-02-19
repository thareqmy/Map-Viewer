
#include "Pixel.h"

Pixel::Pixel() {
	PPoint.x = 0;
	PPoint.y = 0;
	PColor.r = 0;
	PColor.b = 0;
	PColor.g = 0;
}

Pixel::Pixel(Point p, Color c) {
	PPoint = p;
	PColor = c;
}

Pixel::Pixel(int x, int y, int r, int g, int b) {
	PPoint.x = x;
	PPoint.y = y;
	PColor.r = r;
	PColor.b = b;
	PColor.g = g;
}
