#pragma once
#include "header.h"

using namespace std;
using namespace cv;

/********************全局变量声明*********************/
//static Mat src = imread("./img/src.jpg");

/**********************函数声明**********************/

//图像预处理函数（测试）
vector<Mat> preProcess(Mat src, vector<Mat> result);

//寻找数字串区域的函数，返回矩形轮廓
vector<Rect> findStringArea(Mat src);

//分离数字区域，返回区域的图片
Mat separateStringArea(Mat src, Rect rectArea);

//对数字串区域排序，按照从上到下
vector<Rect> sortStringArea(vector<Rect> srcRect);