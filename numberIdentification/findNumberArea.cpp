#include"header.h"

//寻找数字串中单个数字的区域范围，返回矩形轮廓
vector<Rect> findNumberArea(Mat src, int thresholdVal)
{
	vector<Rect> dstRect;
	Mat dst;

	//通道分离
	vector<Mat> Vchannels;
	Mat channel_b, channel_g, channel_r;
	split(src, Vchannels);
	channel_b = Vchannels.at(0);
	channel_g = Vchannels.at(1);
	channel_r = Vchannels.at(2);

	channel_r.copyTo(dst);				//红色通道对比度最高

	//手动阈值化
	threshold(dst, dst, 190, 255, CV_THRESH_BINARY);

	//腐蚀膨胀操作
	Mat kernel = getStructuringElement(MORPH_RECT, Size(15, 2), Point(-1, -1));	//横向矩形核
	erode(dst, dst, kernel, Point(-1, -1), 1, 0);
	kernel = getStructuringElement(MORPH_RECT, Size(2, 300), Point(-1, -1));	//纵向矩形核
	dilate(dst, dst, kernel, Point(-1, -1), 1, 0);

	imshow("show", dst);

	return dstRect;
}
