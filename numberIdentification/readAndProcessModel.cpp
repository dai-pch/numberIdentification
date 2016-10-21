#include"header.h"

//读入并处理模板，建立匹配信息
vector<Point> readAndProcessModel(void)
{
	vector<Point> info;

	Mat m0 = imread("./img/m0.jpg", 0);
	adaptiveThreshold(m0, m0, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 121, -45);
	Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(6, 6), Point(-1, -1));
	erode(m0, m0, kernel, Point(-1, -1), 1, 0);
	dilate(m0, m0, kernel, Point(-1, -1), 1, 0);
	dilate(m0, m0, kernel, Point(-1, -1), 1, 0);
	erode(m0, m0, kernel, Point(-1, -1), 1, 0);
	imwrite("./img/nm0.jpg", m0);



	Mat m1 = imread("./img/m1.jpg", 0);
	adaptiveThreshold(m1, m1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 121, -45);
	erode(m1, m1, kernel, Point(-1, -1), 1, 0);
	dilate(m1, m1, kernel, Point(-1, -1), 1, 0);
	dilate(m1, m1, kernel, Point(-1, -1), 1, 0);
	erode(m1, m1, kernel, Point(-1, -1), 1, 0);
	imwrite("./img/nm1.jpg", m1);

	Mat m2 = imread("./img/m2.jpg", 0);
	adaptiveThreshold(m2, m2, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 121, -45);
	erode(m2, m2, kernel, Point(-1, -1), 1, 0);
	dilate(m2, m2, kernel, Point(-1, -1), 1, 0);
	dilate(m2, m2, kernel, Point(-1, -1), 1, 0);
	erode(m2, m2, kernel, Point(-1, -1), 1, 0);
	imwrite("./img/nm2.jpg", m2);

	Mat m3 = imread("./img/m3.jpg", 0);
	adaptiveThreshold(m3, m3, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 121, -45);
	erode(m3, m3, kernel, Point(-1, -1), 1, 0);
	dilate(m3, m3, kernel, Point(-1, -1), 1, 0);
	dilate(m3, m3, kernel, Point(-1, -1), 1, 0);
	erode(m3, m3, kernel, Point(-1, -1), 1, 0);
	imwrite("./img/nm3.jpg", m3);

	Mat m4 = imread("./img/m4.jpg", 0);
	adaptiveThreshold(m4, m4, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 121, -45);
	erode(m4, m4, kernel, Point(-1, -1), 1, 0);
	dilate(m4, m4, kernel, Point(-1, -1), 1, 0);
	dilate(m4, m4, kernel, Point(-1, -1), 1, 0);
	erode(m4, m4, kernel, Point(-1, -1), 1, 0);
	imwrite("./img/nm4.jpg", m4);

	Mat m5 = imread("./img/m5.jpg", 0);
	adaptiveThreshold(m5, m5, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 121, -45);
	erode(m5, m5, kernel, Point(-1, -1), 1, 0);
	dilate(m5, m5, kernel, Point(-1, -1), 1, 0);
	dilate(m5, m5, kernel, Point(-1, -1), 1, 0);
	erode(m5, m5, kernel, Point(-1, -1), 1, 0);
	imwrite("./img/nm5.jpg", m5);

	Mat m6 = imread("./img/m6.jpg", 0);
	adaptiveThreshold(m6, m6, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 121, -45);
	erode(m6, m6, kernel, Point(-1, -1), 1, 0);
	dilate(m6, m6, kernel, Point(-1, -1), 1, 0);
	dilate(m6, m6, kernel, Point(-1, -1), 1, 0);
	erode(m6, m6, kernel, Point(-1, -1), 1, 0);
	imwrite("./img/nm6.jpg", m6);

	Mat m7 = imread("./img/m7.jpg", 0);
	adaptiveThreshold(m7, m7, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 121, -45);
	erode(m7, m7, kernel, Point(-1, -1), 1, 0);
	dilate(m7, m7, kernel, Point(-1, -1), 1, 0);
	dilate(m7, m7, kernel, Point(-1, -1), 1, 0);
	erode(m7, m7, kernel, Point(-1, -1), 1, 0);
	imwrite("./img/nm7.jpg", m7);

	Mat m9 = imread("./img/m9.jpg", 0);
	adaptiveThreshold(m9, m9, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 121, -45);
	erode(m9, m9, kernel, Point(-1, -1), 1, 0);
	dilate(m9, m9, kernel, Point(-1, -1), 1, 0);
	dilate(m9, m9, kernel, Point(-1, -1), 1, 0);
	erode(m9, m9, kernel, Point(-1, -1), 1, 0);
	imwrite("./img/nm9.jpg", m9);

	return info;
}