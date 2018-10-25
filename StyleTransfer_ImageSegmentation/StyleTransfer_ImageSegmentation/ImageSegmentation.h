#pragma once

#include "opencv2\opencv.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

#define MAXPIXEL 256
#define UNKNOWN 128
#define BLACK 0
#define WHITE 255


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

extern int nHeight, nWidth;
extern Mat procImg;

bool isBoundary(int x, int y);

void pre_processing(Mat inputImg);
void edgeDetection(Mat&, Mat&);
void LinearContrastStretching(Mat& in, Mat& out, int r1, int s1, int r2, int s2);
void imageCombine(Mat& showImg, Mat& outputImg);

void expand_seleced(Mat& outImg, vector<PixelNode>& frontier, int x, int y, uchar new_label);
void expand_otherwise(Mat& outImg, vector<PixelNode>& frontier, int x, int y, int pixel, uchar new_label);
void watershed(Mat& selectImg, Mat& outputImg);