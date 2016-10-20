#include"header.h"

//Ѱ�����ִ�����ĺ��������ؾ�������

vector<Rect> findStringArea(Mat src)
{
	Mat dst, temp_mask;
	//ͨ������
	vector<Mat> Vchannels;
	Mat channel_b, channel_g, channel_r;
	split(src, Vchannels);
	channel_b = Vchannels.at(0);
	channel_g = Vchannels.at(1);
	channel_r = Vchannels.at(2);

	channel_r.copyTo(dst);				//��ɫͨ���Աȶ����

	//�ֶ���ֵ��
	threshold(dst, dst, 155, 255, CV_THRESH_BINARY);

	//��һ������
	Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(7, 7), Point(-1, -1));	//Բ�ˣ�Ч���Ϻ�
	erode(dst, dst, kernel, Point(-1, -1), 1, 0);
	dilate(dst, dst, kernel, Point(-1, -1), 1, 0);
	dilate(dst, dst, kernel, Point(-1, -1), 1, 0);
	erode(dst, dst, kernel, Point(-1, -1), 1, 0);

	//�������ִ��õ�ģ��
	boxFilter(dst, temp_mask, -1, Size(81, 81));
	threshold(temp_mask, temp_mask, 20, 255, CV_THRESH_BINARY);
	//��һЩ���ţ������κ�������
	Mat kernel_mask = getStructuringElement(MORPH_RECT, Size(50, 1), Point(-1, -1));
	erode(temp_mask, temp_mask, kernel_mask, Point(-1, -1), 1, 0);
	dilate(temp_mask, temp_mask, kernel_mask, Point(-1, -1), 1, 0);
	dilate(temp_mask, temp_mask, kernel_mask, Point(-1, -1), 1, 0);
	erode(temp_mask, temp_mask, kernel_mask, Point(-1, -1), 1, 0);

	kernel_mask = getStructuringElement(MORPH_RECT, Size(20, 20), Point(-1, -1));
	erode(temp_mask, temp_mask, kernel_mask, Point(-1, -1), 1, 0);

	Mat mask_contours;
	temp_mask.copyTo(mask_contours);
	vector<vector<Point>>contours;
	vector<Vec4i> hierarchy;
	findContours(mask_contours, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
	vector<vector<Point>> contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
		boundRect[i] = boundingRect(Mat(contours_poly[i]));
	}

	return boundRect;
}