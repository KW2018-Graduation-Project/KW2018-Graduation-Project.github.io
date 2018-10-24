#pragma once

#include "ImageSegmentation.h"
//#include <node/node.h>

/*unsigned char
white[3] = { 255,255,255 },
white_111[3] = { 1,1,1 },
black[3] = { 0,0,0 },
red[3] = { 0,0,255 },
grey[3] = { 127,127,127 },
green[3] = { 0,255,0 },
blue[3] = { 255,0,0 },
yellow[3] = { 0,255,255 },
magenta[3] = { 255,0,255 },
orange[3] = { 0,90,255 },
middle[3] = { 127,127,127 },
purple[3] = { 186,32,175 };

typedef struct { unsigned char r, g, b; } rgb;
rgb colors[255];

// random color
rgb random_rgb() {
rgb c;

c.r = (unsigned char)(rand() % 255);
c.g = (unsigned char)(rand() % 255);
c.b = (unsigned char)(rand() % 255);

return c;
}

void randomColorForLabels()
{
for (int i = 0; i < 255; i++)
colors[i] = random_rgb();
}

void draw_results(Mat &image, Mat &result, unsigned char* color)
{
for (int x = 0; x < image.cols; x++) {
for (int y = 0; y < image.rows; y++) {
if (result.at<uchar>(x, y) == 255) {
image.at<Vec3b>(x, y)[0] = color[0];
image.at<Vec3b>(x, y)[1] = color[1];
image.at<Vec3b>(x, y)[2] = color[2];
}
}
}
}

Mat colorizeLabelImage(Mat &image)
{
int width = image.cols;
int height = image.rows;

Mat output = Mat::zeros(width, height, CV_8UC3);

for (int x = 0; x < width; x++) {
for (int y = 0; y < height; y++) {
int comp = image.at<uchar>(x, y);
output.at<Vec3b>(x, y)[0] = colors[comp].r;
output.at<Vec3b>(x, y)[1] = colors[comp].g;
output.at<Vec3b>(x, y)[2] = colors[comp].b;
}
}
return output;
}*/

Mat inputImg, outputImg, selectImg;
bool clicked;
int prevX, prevY;

void mouseCallback(int event, int x, int y, int flags, void* param);

int main(int argc, char **argv) {
	const char* filename = "cat.jpg";
	inputImg = imread(filename, IMREAD_COLOR);

	selectImg = Mat(inputImg.rows, inputImg.cols, CV_8UC3, Scalar(255, 255, 255));
	outputImg = Mat(inputImg.rows, inputImg.cols, CV_8UC3, Scalar(0, 0, 0));

	pre_processing(inputImg);

	imshow("input Image", inputImg);
	//imshow("selected Image", selectImg);
	imshow("output Image", outputImg);

	clicked = false;
	setMouseCallback("input Image", mouseCallback);

	waitKey(0);
	return 0;
}

void mouseCallback(int event, int curX, int curY, int flags, void* param) {
	switch (event) {
	case CV_EVENT_MOUSEMOVE:
		if (!clicked) return;
		line(inputImg, Point(prevX, prevY), Point(curX, curY), Scalar(0, 0, 255), 2);
		line(selectImg, Point(prevX, prevY), Point(curX, curY), Scalar(0, 0, 0), 2);
		prevX = curX;
		prevY = curY;
		imshow("input Image", inputImg);
		//imshow("selected Image", selectImg);
		break;
	case CV_EVENT_LBUTTONDOWN:
		prevX = curX;
		prevY = curY;
		clicked = true;
		break;
	case CV_EVENT_LBUTTONUP:
		clicked = false;
		outputImg = watershed(selectImg);
		imshow("output Image", outputImg);
		break;
	}
}