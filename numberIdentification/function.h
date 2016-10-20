#pragma once
#include "header.h"

using namespace std;
using namespace cv;

/********************全局变量声明*********************/
//static Mat src = imread("./img/src.jpg");

/**********************函数声明**********************/
vector<Mat> preProcess(Mat src, vector<Mat> result);
vector<Rect> findStringArea(Mat src);
Mat separateStringArea(Mat src, Rect rectArea);