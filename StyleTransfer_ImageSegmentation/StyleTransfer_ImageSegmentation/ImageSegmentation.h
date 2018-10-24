#pragma once

#include "opencv2\opencv.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

#define MAXPIXEL 256

class PixelNode {
private:
	int px;
	int py;
public:
	PixelNode() : px(0), py(0) {}
	PixelNode(int x, int y) : px(x), py(y) {}

	int getX() { return px; }
	int getY() { return py; }
};

extern int height, width;
extern Mat procImg;

void pre_processing(Mat inputImg);
void edgeDetection(Mat&, Mat&);

void expand_seleced(Mat& outImg, vector<PixelNode>& frontier, int x, int y, int color, int new_color);
void expand_otherwise(Mat& outImg, vector<PixelNode>& frontier, int x, int y, int color, int new_color);
void FloodFill8(Mat& outImg, int x, int y, int new_color);
Mat watershed(Mat& selectImg);
uchar GetNeighborPixel(Mat &outputImg, int x, int y);






/*class PixelNode {
int px;
int py;
float value;
public:
PixelNode() : px(0), py(0), value(0) {}
PixelNode(int i) : px(i), py(i), value(0) {}
PixelNode(int x, int y, float v) {
px = x;
py = y;
value = v;
}
PixelNode(int x, int y) {
px = x;
py = y;
value = 0;
}
PixelNode(const PixelNode& p) : px(p.px), py(p.py), value(p.value) {}

bool operator< (const PixelNode &b) const {
return value < b.getValue();
}
bool operator> (const PixelNode &b) const {
return value > b.getValue();
}
bool operator==(const PixelNode& pt) const {
return  pt.getX() == px && pt.getY() == py;
}
bool operator!=(const PixelNode& pt) const {
return !(pt == *this);
}
PixelNode operator+(const PixelNode& pt) const {
return PixelNode(px + pt.getX(), py + pt.getY());
}
PixelNode& operator+=(const PixelNode& pt) {
px += pt.getX();
py += pt.getY();
return *this;
}
float getValue() const {
return value;
}
int getX() const {
return px;
}
int getY() const {
return py;
}
};*/





/*int Dx, Dy;
Mat OriginImage, OriginImage_rgb, OriginImage_gray;
Mat EdgeImage_gray, EdgeImage_rgb;
Mat canvas, gcanvas;
Mat marker, marker_neg, gradmarker;
Mat result, result_ok0, result_ok1, result_ok2;
Mat marker_disp;*/

//void canvasSetting();j
//Mat imageUpload(const char* filename);

//void canvasSetting();







/*int draw_type = 1;
bool clicked = false;
volatile unsigned int btt = 0;
int mx = 0, my = 0, px = 0, py = 0, mouse_x = 0, mouse_y = 0, prev_x = 0, prev_y = 0;*/