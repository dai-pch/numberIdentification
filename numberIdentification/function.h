#pragma once
#include "header.h"

using namespace std;
using namespace cv;

/********************ȫ�ֱ�������*********************/
static Mat src = imread("./img/src.jpg");

/**********************��������**********************/
Mat preProcess(Mat src);