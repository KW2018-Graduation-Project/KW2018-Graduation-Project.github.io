#pragma once

#include "ImageSegmentation.h"

int height, width;
Mat procImg;

void pre_processing(Mat inputImg) {
	height = inputImg.rows;
	width = inputImg.cols;

	procImg = imread("edge.jpg", IMREAD_GRAYSCALE);
	//EdgeDetection();
}

void edgeDetection(Mat &input, Mat &output) {
	Mat BlurImage;
	blur(input, BlurImage, Size(5, 5));

	Mat sobelX, sobelY;
	Sobel(BlurImage, sobelX, CV_8U, 1, 0);
	Sobel(BlurImage, sobelY, CV_8U, 0, 1);
	addWeighted(sobelX, 0.5, sobelY, 0.5, 0, output);
}

void imageCombine(Mat& showImg, Mat& outputImg) {
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			if (outputImg.at<uchar>(h, w) == BLACK) {
				int colorB = (showImg.at<Vec3b>(h, w)[0] - 100 < 0) ? 0 : showImg.at<Vec3b>(h, w)[0] - 100;
				int colorG = (showImg.at<Vec3b>(h, w)[1] - 100 < 0) ? 0 : showImg.at<Vec3b>(h, w)[1] - 100;
				int colorR = (showImg.at<Vec3b>(h, w)[2] - 100 < 0) ? 0 : showImg.at<Vec3b>(h, w)[2] - 100;
				
				showImg.at<Vec3b>(h, w)[0] = colorB;
				showImg.at<Vec3b>(h, w)[1] = colorG;
				showImg.at<Vec3b>(h, w)[2] = colorR;
			}
		}
	}
}

/*void canvasSetting() {
OriginImage_rgb.copyTo(canvas);
EdgeImage_rgb.copyTo(gcanvas);

marker = Mat::zeros(Dx, Dy, CV_8U);
marker_neg = Mat::zeros(Dx, Dy, CV_8U);
gradmarker = Mat::zeros(Dx, Dy, CV_8U);

result = Mat::ones(Dx, Dy, CV_8S) * -1;
result_ok0 = Mat::zeros(Dx, Dy, CV_8U);
result_ok1 = Mat::zeros(Dx, Dy, CV_8U);
result_ok2 = Mat::zeros(Dx, Dy, CV_8U);

marker_disp = Mat::zeros(Dx, Dy, CV_8UC3);
}*/