#pragma once

#include "watershedSegmentation.h"

using namespace cv;

Mat inputImg, maskImg, outputImg, showImg;
bool clicked;
int prevX, prevY;
uchar flag;

WatershedSegmenter segmenter;

void mouseCallback(int event, int x, int y, int flags, void* param);

int main(int argc, char **argv) {
	flag = OBJECT;
	const char* filename = "dog.jpg";
	
	inputImg = imread(filename, IMREAD_COLOR);
	nHeight = inputImg.rows;
	nWidth = inputImg.cols;
	
	maskImg = Mat(inputImg.size(), CV_8U, Scalar(0));
	rectangle(maskImg, Point(5, 5), Point(nWidth - 1, nHeight - 1), Scalar(BACKGROUNT), 3);

	inputImg.copyTo(showImg);

	outputImg = Mat(nHeight, nWidth, CV_8UC1, Scalar(0));

	imshow("StyleTransfer", showImg);

	clicked = false;
	setMouseCallback("StyleTransfer", mouseCallback);

	waitKey(0);
	return 0;
}

void mouseCallback(int event, int curX, int curY, int flags, void* param) {
	switch (event) {
	case CV_EVENT_MOUSEMOVE:
		if (!clicked) return;

		line(showImg, Point(prevX, prevY), Point(curX, curY), Scalar(0, 0, 255), 10);
		line(maskImg, Point(prevX, prevY), Point(curX, curY), Scalar(flag), 10);

		prevX = curX;
		prevY = curY;

		imshow("StyleTransfer", showImg);

		break;
	case CV_EVENT_LBUTTONDOWN:
		clicked = true;

		prevX = curX;
		prevY = curY;

		break;
	case CV_EVENT_LBUTTONUP:
		clicked = false;

		segmenter.setMarkers(maskImg);
		segmenter.process(inputImg);

		inputImg.copyTo(showImg);
		outputImg = segmenter.getSegmentation();
		imageCombine(showImg, outputImg);

		imshow("StyleTransfer", showImg);

		int fff;
		std::cin >> fff;
		if (fff == 0) flag = BACKGROUNT;
		else if (fff == 1) flag = OBJECT;
		break;
	}
}