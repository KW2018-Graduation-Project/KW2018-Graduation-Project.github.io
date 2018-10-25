#pragma once

#include "ImageSegmentation.h"

int nHeight, nWidth;
Mat procImg;

void pre_processing(Mat inputImg) {
	nHeight = inputImg.rows;
	nWidth = inputImg.cols;

	Mat grayImg = Mat(nHeight, nWidth, CV_8UC1, Scalar(BLACK));
	procImg = Mat(nHeight, nWidth, CV_8UC1, Scalar(BLACK));
	Mat histImg, blurImg, gradientImg, normImg;
	cvtColor(inputImg, grayImg, CV_BGR2GRAY);
	equalizeHist(grayImg, histImg);
	GaussianBlur(grayImg, blurImg, Size(9, 9), 0);
	edgeDetection(blurImg, gradientImg);
	normalize(gradientImg, normImg, 10.0, 255.0, NORM_MINMAX);
	GaussianBlur(normImg, procImg, Size(3, 3), 0);

	for (int h = 0; h < nHeight; h++) {
		for (int w = 0; w < nWidth; w++) {
			int pix = procImg.at<uchar>(h, w);
			if (pix % 2 == 1) {
				procImg.at<uchar>(h, w) = pix - 1;
			}
		}
	}
	

	//LinearContrastStretching(grayImg, procImg, 40, 25, 230, 250);
	//normalize(grayImg, procImg, 0.0, 255.0, NORM_MINMAX);
	//equalizeHist(grayImg, histImg);
	//blur(histImg, procImg, Size(5, 5));
	//GaussianBlur(histImg, procImg, Size(5, 5), 0);
	//edgeDetection(blurImg, gradientImg);
	//normalize(gradientImg, procImg, 10.0, 255.0, NORM_MINMAX);
}

void edgeDetection(Mat &in, Mat &out) {
	Mat sobelX, sobelY;
	Sobel(in, sobelX, CV_8U, 1, 0);
	Sobel(in, sobelY, CV_8U, 0, 1);
	addWeighted(sobelX, 0.5, sobelY, 0.5, 0, out);
}

void LinearContrastStretching(Mat& in, Mat& out, int r1, int s1, int r2, int s2) {
	for (int h = 0; h < nHeight; h++) {
		for (int w = 0; w < nWidth; w++) {
			int pixel = in.at<uchar>(h, w);
			int new_pix;
			
			if (0 <= pixel && pixel <= r1)			new_pix = s1 / r1 * pixel;
			else if (r1 < pixel && pixel <= r2)		new_pix = ((s2 - s1) / (r2 - r1)) * (pixel - r1) + s1;
			else if (r2 < pixel && pixel <= 255)	new_pix = ((255 - s2) / (255 - r2)) * (pixel - r2) + s2;

			out.at<uchar>(h, w) = new_pix;
		}
	}
}

void imageCombine(Mat& showImg, Mat& outputImg) {
	for (int h = 0; h < nHeight; h++) {
		for (int w = 0; w < nWidth; w++) {
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