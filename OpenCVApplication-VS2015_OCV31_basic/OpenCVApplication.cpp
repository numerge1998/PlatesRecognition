// OpenCVApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "common.h"

using namespace std;

void test()
{
	char fname[MAX_PATH];
	while (openFileDlg(fname))
	{
		Mat src,src1,dst1,cat,cat1,cont, dst, gauss;
		src = imread(fname, CV_LOAD_IMAGE_COLOR);
		resizeImg(src,src1,520,true);
		cvtColor(src1, dst, COLOR_BGR2GRAY);
		bilateralFilter(dst,dst1,10,15,15);
		//blur(dst, dst1, Size(3, 3));
		Canny(dst1,cat,150,400);
		Mat test = Mat::zeros(cat.size(), cat.type());
		Mat test1 = Mat::zeros(cat.size(), cat.type());
		Mat test12 = Mat::zeros(cat.size(), cat.type());
		Mat final = Mat::zeros(src1.size(), src1.type());
		for (int i = 0;i < cat.rows;i++)
			for (int j = 0;j < cat.cols;j++)
				test.at<uchar>(i, j) = cat.at<uchar>(i, j);
		for (int i = 0;i < cat.rows;i++)
			for (int j = 0;j < cat.cols;j++)
				test1.at<uchar>(i, j) = 255;
		for (int i = 0;i < cat.rows;i++)
			for (int j = 0;j < cat.cols;j++)
				test12.at<uchar>(i, j) = 255;
		/*for (int i = 0;i < src1.rows;i++)
			for (int j = 0;j < src1.cols;j++) {
				final.at< Vec3b>(i, j) = Vec3b(255,255,255);
			}*/
		vector<vector<Point>> wtf;
		
		vector<Point> wtf1;
		findContours(test,wtf,RETR_LIST,CHAIN_APPROX_NONE);
		vector<vector<Point>> index(wtf.size());
		int s = 0;
		for (int i = 0;i < wtf.size();i++) {	
			approxPolyDP(wtf[i], wtf1, 0.018*arcLength(wtf[i], true), true);
			if (wtf1.size() == 4) {
				//drawContours(test1, wtf, i, (255, 0, 0), 1);
				if (abs(wtf1[1].x - wtf1[0].x) >= 220 && abs(wtf1[1].x - wtf1[0].x) <= 300 && abs(wtf1[1].y - wtf1[2].y) >= 40 && abs(wtf1[1].y - wtf1[2].y) <= 100 
					//|| abs(wtf1[1].x - wtf1[0].x) >= 100 && abs(wtf1[1].x - wtf1[0].x) <= 500 && abs(wtf1[1].y - wtf1[2].y) >= 10 && abs(wtf1[1].y - wtf1[2].y) <= 400
					) {
					/*test12.at<uchar>(wtf1[0].x, wtf1[0].y) = 0;
					test12.at<uchar>(wtf1[0].x, wtf1[0].y + 1) = 0;
					test12.at<uchar>(wtf1[0].x, wtf1[0].y - 1) = 0;
					test12.at<uchar>(wtf1[0].x + 1, wtf1[0].y) = 0;
					test12.at<uchar>(wtf1[0].x - 1, wtf1[0].y) = 0;
					test12.at<uchar>(wtf1[1].x, wtf1[1].y) = 0;
					test12.at<uchar>(wtf1[1].x, wtf1[1].y + 1) = 0;
					test12.at<uchar>(wtf1[1].x, wtf1[1].y - 1) = 0;
					test12.at<uchar>(wtf1[1].x + 1, wtf1[1].y) = 0;
					test12.at<uchar>(wtf1[1].x - 1, wtf1[1].y) = 0;
					test12.at<uchar>(wtf1[2].x, wtf1[2].y) = 0;
					test12.at<uchar>(wtf1[2].x, wtf1[2].y + 1) = 0;
					test12.at<uchar>(wtf1[2].x, wtf1[2].y - 1) = 0;
					test12.at<uchar>(wtf1[2].x + 1, wtf1[2].y) = 0;
					test12.at<uchar>(wtf1[2].x - 1, wtf1[2].y) = 0;
					test12.at<uchar>(wtf1[3].x, wtf1[3].y) = 0;
					test12.at<uchar>(wtf1[3].x, wtf1[3].y + 1) = 0;
					test12.at<uchar>(wtf1[3].x, wtf1[3].y - 1) = 0;
					test12.at<uchar>(wtf1[3].x + 1, wtf1[3].y) = 0;
					test12.at<uchar>(wtf1[3].x - 1, wtf1[3].y) = 0;*/
					printf("%d  %d %d %d\n", wtf1[0].x, wtf1[1].x, wtf1[2].x, wtf1[3].x);
					index[s] = wtf1;
					s++;
				}
			}
		}
		printf("%d \n", s);
		for (int i = 0;i < s;i++) {
			//for (Point p1 : p) {
			test12.at<uchar>(index[i][3].y, index[i][3].x) = 0;
			test12.at<uchar>(index[i][3].y+1, index[i][3].x) = 0;
			test12.at<uchar>(index[i][3].y-1, index[i][3].x) = 0;
			test12.at<uchar>(index[i][3].y, index[i][3].x+1) = 0;
			test12.at<uchar>(index[i][3].y, index[i][3].x-1) = 0;

			test12.at<uchar>(index[i][2].y, index[i][2].x) = 90;
			test12.at<uchar>(index[i][2].y + 1, index[i][2].x) = 90;
			test12.at<uchar>(index[i][2].y - 1, index[i][2].x) = 90;
			test12.at<uchar>(index[i][2].y, index[i][2].x + 1) = 90;
			test12.at<uchar>(index[i][2].y, index[i][2].x - 1) = 90;

			test12.at<uchar>(index[i][1].y, index[i][1].x) = 140;
			test12.at<uchar>(index[i][1].y + 1, index[i][1].x) = 140;
			test12.at<uchar>(index[i][1].y - 1, index[i][1].x) = 140;
			test12.at<uchar>(index[i][1].y, index[i][1].x + 1) = 140;
			test12.at<uchar>(index[i][1].y, index[i][1].x - 1) = 140;

			test12.at<uchar>(index[i][0].y, index[i][0].x) = 210;
			test12.at<uchar>(index[i][0].y + 1, index[i][0].x) = 210;
			test12.at<uchar>(index[i][0].y - 1, index[i][0].x) = 210;
			test12.at<uchar>(index[i][0].y, index[i][0].x + 1) = 210;
			test12.at<uchar>(index[i][0].y, index[i][0].x - 1) = 210;
		}
		drawContours(test1, index, -1, (255, 0, 0), 1);

		int xmin[20],ymin[20],xmax[20],ymax[20];
		for (int k = 0;k < s;k++) {
			xmin[k] = min(index[k][0].x, min(index[k][1].x, min(index[k][2].x, index[k][3].x)));
			ymin[k] = min(index[k][0].y, min(index[k][1].y, min(index[k][2].y, index[k][3].y)));
			xmax[k] = max(index[k][0].x, max(index[k][1].x, max(index[k][2].x, index[k][3].x)));
			ymax[k] = max(index[k][0].y, max(index[k][1].y, max(index[k][2].y, index[k][3].y)));
		}
		printf("xmin : %d ymin : %d xmax : %d ymax : %d\n", xmin, ymin, xmax, ymax);

		for (int i = 0;i < src1.rows;i++)
			for (int j = 0;j < src1.cols;j++)
				final.at<Vec3b>(i, j) = { 255,255,255 };

		char izz = 48;
		for (int k = 0;k < s;k++) {
			for (int i = 0;i < src1.rows;i++)
				for (int j = 0;j < src1.cols;j++)
					if (i >= ymin[k] - 1 && i <= ymax[k] + 1 && j >= xmin[k] - 1 && j <= xmax[k] + 1)
						final.at<Vec3b>(i, j) = src1.at<Vec3b>(i, j);
			char src[50], dest[50];
			strcpy(src, ".jpg");
			*dest = izz;
			*(dest + 1) = '\0';
			strcat(dest, src);

			int x = printf("%s\n", dest);
			izz += 1;
			imwrite(dest, final);
			for (int i = 0;i < src1.rows;i++)
				for (int j = 0;j < src1.cols;j++)
					final.at<Vec3b>(i, j) = { 255,255,255 };
		}

		for (int k = 0;k < s;k++) 
			for (int i = 0;i < src1.rows;i++)
				for (int j = 0;j < src1.cols;j++)
					if (i >= ymin[k] - 1 && i <= ymax[k] + 1 && j >= xmin[k] - 1 && j <= xmax[k] + 1)
						final.at<Vec3b>(i, j) = src1.at<Vec3b>(i, j);

		for (int i = 0;i < test1.rows;i++)
			for (int j = 0;j < test1.cols;j++)
				if (test1.at<uchar>(i, j) == 0) {
					src1.at<Vec3b>(i, j) = { 0,0,255 };
					src1.at<Vec3b>(i+1, j) = { 0,0,255 };
					src1.at<Vec3b>(i, j+1) = { 0,0,255 };
					src1.at<Vec3b>(i+2, j) = { 0,0,255 };
					src1.at<Vec3b>(i, j+2) = { 0,0,255 };
				}
		//printf("%d\n", wtf[2].size());
		//imshow("input image", src);
		imshow("input image resized", src1);
		imshow("gray resized", dst);
		imshow("estompata", dst1);
		imshow("canny", cat);
		imshow("canny1", test);
		imshow("contururi", test1);
		imshow("punctele", test12);
		imshow("plates", final);
		waitKey();
	}
}


int main()
{
	test();
	return 0;
}