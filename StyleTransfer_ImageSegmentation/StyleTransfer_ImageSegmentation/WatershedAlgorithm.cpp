#pragma once

#include "ImageSegmentation.h"

#define DIR 4

int dir_x[8] = { -1, 1, 0, 0, -1, -1, 1, 1 };
int dir_y[8] = { 0, 0, -1, 1, -1, -1, -1,1 };

bool isBoundary(int x, int y) {
	if (x < 0) return false;
	if (y < 0) return false;
	if (x > height-1) return false;
	if (y > width-1) return false;
	return true;
}

void expand_seleced(Mat& outImg, vector<PixelNode>& frontier, int x, int y, uchar new_label) {
	int pixel = procImg.at<uchar>(x, y);

	for (int i = 0; i < DIR; i++) {
		int nx = x + dir_x[i];
		int ny = y + dir_y[i];

		if (!isBoundary(x, y)) return;

		if (pixel == new_label && outImg.at<uchar>(x, y) != new_label) {
			outImg.at<uchar>(x, y) = new_label;
			frontier.push_back(PixelNode(x, y));
		}
	}
}

void expand_otherwise(Mat& outImg, vector<PixelNode>& frontier, int x, int y, int pixel, uchar new_label) {
	for (int i = 0; i < DIR; i++) {
		int nx = x + dir_x[i];
		int ny = y + dir_y[i];

		if (!isBoundary(nx, ny)) continue;

		int ssss = procImg.at<uchar> (nx, ny);

		if (procImg.at<uchar>(nx, ny) <= pixel && outImg.at<uchar>(nx, ny) == UNKNOWN) {

			//cout << (int)procImg.at<uchar>(nx, ny) << endl;

			outImg.at<uchar>(nx, ny) = new_label;
			frontier.push_back(PixelNode(nx, ny));
		}
	}
}

void watershed(Mat& selectImg, Mat& outImg) {
	vector<vector<PixelNode> > pixels(MAXPIXEL);
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			uchar sel_pix = selectImg.at<uchar>(h, w);
			if (sel_pix == BLACK)		pixels[BLACK].push_back(PixelNode(h, w));
			else if (sel_pix == WHITE)	pixels[WHITE].push_back(PixelNode(h, w));
			else		pixels[procImg.at<uchar>(h, w)].push_back(PixelNode(h, w));
		}
	}

	vector<PixelNode> frontier;
	outImg.at<uchar>(0, 0) = BLACK;
	frontier.push_back(PixelNode(0, 0));

	int size = pixels[BLACK].size();
	for (int i = 0; i<size; i++) {
		PixelNode node = pixels[BLACK][i];
		if (outImg.at<uchar>(node.getX(), node.getY()) == UNKNOWN) {
			outImg.at<uchar>(node.getX(), node.getY()) = BLACK;
			frontier.push_back(node);
			expand_seleced(outImg, frontier, node.getX(), node.getY(), BLACK);
		}
	}

	size = pixels[WHITE].size();
	for (int i = 0; i<size; i++) {
		PixelNode node = pixels[WHITE][i];
		if (outImg.at<uchar>(node.getX(), node.getY()) == UNKNOWN) {
			outImg.at<uchar>(node.getX(), node.getY()) = WHITE;
			frontier.push_back(node);
			expand_seleced(outImg, frontier, node.getX(), node.getY(), WHITE);
		}
	}

	for (int pix = 1; pix < MAXPIXEL; pix++) {

		int size = pixels[pix].size();
		for (int i = 0; i < size; i++) {
			PixelNode node = pixels[pix][i];

			for (int j = 0; j < DIR; j++) {
				int nx = node.getX() + dir_x[j];
				int ny = node.getY() + dir_y[j];

				if (!isBoundary(nx, ny)) continue;

				int neighbor_label = outImg.at<uchar>(nx, ny);
				if (neighbor_label != UNKNOWN) {
					outImg.at<uchar>(node.getX(), node.getY()) = neighbor_label;
					frontier.push_back(node);
				}
			}
		}

		while (!frontier.empty()) {
			PixelNode node = frontier.back();
			frontier.pop_back();

			int label = outImg.at<uchar>(node.getX(), node.getY());
			expand_otherwise(outImg, frontier, node.getX(), node.getY(), pix, label);
		}
	}
}