#pragma once

#include "ImageSegmentation.h"

void expand_seleced(Mat& outImg, vector<PixelNode>& frontier, int x, int y, int color, int new_color) {
	int pixel_proc = procImg.at<uchar>(x, y);
	int pixel_out = outImg.at<uchar>(x, y);
	if (pixel_proc == color && pixel_out != new_color) {
		frontier.push_back(PixelNode(x, y));
		outImg.at<uchar>(x, y) = new_color;
	}
}

void expand_otherwise(Mat& outImg, vector<PixelNode>& frontier, int x, int y, int color, int new_color) {
	
}

void FloodFill8(Mat& outImg, int x, int y, int new_color) {
	if (x < 0 || y < 0 || x >= width || y >= height) { cout << "Out of bounds" << endl; return; }

	vector<PixelNode> frontier;
	int w = width - 1;
	int h = height - 1;

	//if (new_color == (*out)(x,y))  return;
	int proc_color = procImg.at<uchar>(x, y);
	frontier.push_back(PixelNode(x, y));
	outImg.at<uchar>(x, y) = new_color;

	while (!frontier.empty())
	{
		PixelNode node = frontier.back();
		frontier.pop_back();

		if (node.getX() > 0)  expand_seleced(outImg, frontier, x - 1, y, proc_color, new_color);
		if (node.getX() < w)  expand_seleced(outImg, frontier, x + 1, y, proc_color, new_color);
		if (node.getY() > 0)  expand_seleced(outImg, frontier, x, y - 1, proc_color, new_color);
		if (node.getY() < h)  expand_seleced(outImg, frontier, x, y + 1, proc_color, new_color);

		if (node.getX() > 0 && p.getY() > 0)  expand_seleced(outImg, frontier, x - 1, y - 1, proc_color, new_color);
		if (node.getX() > 0 && p.getY() < h)  expand_seleced(outImg, frontier, x + 1, y + 1, proc_color, new_color);
		if (node.getX() < w && p.getY() > 0)  expand_seleced(outImg, frontier, x + 1, y - 1, proc_color, new_color);
		if (node.getX() < w && p.getY() < h)  expand_seleced(outImg, frontier, x + 1, y + 1, proc_color, new_color);
	}
}

Mat watershed(Mat &selectImg) {
	Mat outImg = Mat(height, width, CV_8UC3, -1);

	int next_label = 0;

	vector<vector<PixelNode> > pixels(MAXPIXEL);
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			if (selectImg.at<uchar>(h, w) == 0)
				pixels[0].push_back(PixelNode(h, w));
			else
				pixels[procImg.at<uchar>(h, w)].push_back(PixelNode(h, w));
		}
	}

	int size = pixels[0].size();
	for (int i = 0; i<size; i++)
	{
		PixelNode node = pixels[0][i];
		if (outImg.at<uchar>(node.getX(), node.getY()) < 0)
		{
			FloodFill8(outImg, node.getX(), node.getY(), next_label++);
		}
	}

	for (int p = 1; p < MAXPIXEL; p++) {
		vector<PixelNode> frontier;

		int size = pixels[p].size();
		for (int i = 0; i < size; i++) {
			PixelNode node = pixels[p][i];
			int neighbor_pix = GetNeighborPixel(outImg, node.getX(), node.getY());

			//cout << neighbor_pix << endl;

			outImg.at<uchar>(node.getX(), node.getY()) = neighbor_pix;
			frontier.push_back(node);
		}





	}



	return outImg;
}

uchar GetNeighborPixel(Mat &outputImg, int x, int y) {
	uchar pixel = 0;

	if (x > 0) { pixel = outputImg.at<uchar>(x - 1, y); return pixel; }
	if (x < width) { pixel = outputImg.at<uchar>(x + 1, y); return pixel; }
	if (y > 0) { pixel = outputImg.at<uchar>(x, y - 1); return pixel; }
	if (y < height) { pixel = outputImg.at<uchar>(x, y - 1); return pixel; }

	return pixel;
}