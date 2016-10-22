#include"header.h"
#define findNumberAreaWay 1
//寻找数字串中单个数字的区域范围，返回矩形轮廓

#if findNumberAreaWay == 0
vector<Rect> findNumberArea(Mat const src, int thresholdVal, Size kernelSize1, Size kernelSize2)
{
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
	threshold(dst, dst, thresholdVal, 255, CV_THRESH_BINARY);

	//Mat temp_mask;
	//boxFilter(dst, temp_mask, -1, Size(5, 5));
	//threshold(temp_mask, temp_mask, 30, 255, CV_THRESH_BINARY);

	//腐蚀膨胀操作
	Mat kernel = getStructuringElement(MORPH_RECT, kernelSize1, Point(-1, -1));	//横向矩形核
	erode(dst, dst, kernel, Point(-1, -1), 1, 0);
	kernel = getStructuringElement(MORPH_RECT, kernelSize2, Point(-1, -1));	//纵向矩形核
	dilate(dst, dst, kernel, Point(-1, -1), 1, 0);

	//imshow("show", dst);

	//计算外接矩形
	Mat mask_contours;
	dst.copyTo(mask_contours);
	vector<vector<Point>>contours;
	vector<Vec4i> hierarchy;
	findContours(mask_contours, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
	vector<vector<Point>> contours_poly(contours.size());
	vector<Rect> dstRect(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
		dstRect[i] = boundingRect(Mat(contours_poly[i]));
	}

	//按标号排序
	std::sort(dstRect.begin(), dstRect.end(), 
		[](Rect rec1, Rect rec2) {return rec1.x < rec2.x; }
	);

	//计算矩形中心并宽度标准化
	for (int i = 0; i < dstRect.size(); i++)
	{
		Point center(dstRect[i].x + 0.5 * dstRect[i].width, dstRect[i].y + 0.5 * dstRect[i].height);
		dstRect[i].x = center.x - NUM_WIDTH/2;
		dstRect[i].width = NUM_WIDTH;
		dstRect[i].y = center.y - NUM_HEIGHT/2;
		dstRect[i].height = NUM_HEIGHT;
	}

	return dstRect;
}
#endif

#if findNumberAreaWay == 1
vector<Rect> findNumberArea(Mat const src, int thresholdVal, Size kernelSize1, Size kernelSize2)
{
	Mat dst;

	//通道分离
	vector<Mat> Vchannels;
	Mat channel_b, channel_g, channel_r;
	split(src, Vchannels);
	channel_b = Vchannels.at(0);
	channel_g = Vchannels.at(1);
	channel_r = Vchannels.at(2);

	channel_r.copyTo(dst);				//红色通道对比度最高

	//局部自适应阈值
	adaptiveThreshold(dst, dst, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 51, thresholdVal);

	//Mat temp_mask;
	//boxFilter(dst, temp_mask, -1, Size(5, 5));
	//threshold(temp_mask, temp_mask, 30, 255, CV_THRESH_BINARY);

	//腐蚀膨胀操作
	Mat kernel = getStructuringElement(MORPH_RECT, kernelSize1, Point(-1, -1));	//横向矩形核
	erode(dst, dst, kernel, Point(-1, -1), 1, 0);
	kernel = getStructuringElement(MORPH_RECT, kernelSize2, Point(-1, -1));	//纵向矩形核
	dilate(dst, dst, kernel, Point(-1, -1), 1, 0);
	kernel = getStructuringElement(MORPH_RECT, Size(8,1), Point(-1, -1));
	erode(dst, dst, kernel, Point(-1, -1), 1, 0);

	//imshow("show", dst);

	//计算外接矩形
	Mat mask_contours;
	dst.copyTo(mask_contours);
	vector<vector<Point>>contours;
	vector<Vec4i> hierarchy;
	findContours(mask_contours, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
	vector<vector<Point>> contours_poly(contours.size());
	vector<Rect> dstRect(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
		dstRect[i] = boundingRect(Mat(contours_poly[i]));
	}

	//按标号排序
	std::sort(dstRect.begin(), dstRect.end(),
		[](Rect rec1, Rect rec2) {return rec1.x < rec2.x; }
	);

	//计算矩形中心并宽度标准化
	for (int i = 0; i < dstRect.size(); i++)
	{
		Point center(dstRect[i].x + 0.5 * dstRect[i].width, dstRect[i].y + 0.5 * dstRect[i].height);
		dstRect[i].x = center.x - NUM_WIDTH/2;
		dstRect[i].width = NUM_WIDTH;
		dstRect[i].y = center.y - NUM_HEIGHT/2;
		dstRect[i].height = NUM_HEIGHT;
	}

	return dstRect;
}
#endif
