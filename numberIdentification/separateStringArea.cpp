#include"header.h"

//�����������򣬷��������ͼƬ
Mat separateStringArea(Mat src, Rect rectArea)
{
	Mat area;
	src(Rect(rectArea)).copyTo(area);
	return area;
}