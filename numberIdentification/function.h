#pragma once
#include "header.h"

using namespace std;
using namespace cv;

/********************ȫ�ֱ�������*********************/
//static Mat src = imread("./img/src.jpg");

/**********************��������**********************/
vector<Mat> preProcess(Mat src, vector<Mat> result);
vector<Rect> findStringArea(Mat src);
Mat separateStringArea(Mat src, Rect rectArea);