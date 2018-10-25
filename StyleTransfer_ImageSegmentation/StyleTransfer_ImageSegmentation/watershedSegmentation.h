#pragma once

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

#define BACKGROUNT 1
#define OBJECT 255

int nHeight, nWidth;

class WatershedSegmenter {
private:
	Mat markers;
public:
	void setMarkers(const cv::Mat& markerImage) {
		markerImage.convertTo(markers, CV_32S);
	}

	Mat process(const cv::Mat &image) {
		watershed(image, markers);
		return markers;
	}

	Mat getSegmentation() {
		Mat tmp;
		markers.convertTo(tmp, CV_8U);
		return tmp;
	}

	Mat getWatersheds() {
		Mat tmp;
		markers.convertTo(tmp, CV_8U, 255, 255);
		return tmp;
	}
};

void imageCombine(Mat& showImg, Mat& outputImg) {
	for (int h = 0; h < nHeight; h++) {
		for (int w = 0; w < nWidth; w++) {
			if (outputImg.at<uchar>(h, w) == BACKGROUNT) {
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