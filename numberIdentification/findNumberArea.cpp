#include"header.h"

//Ѱ�����ִ��е������ֵ�����Χ�����ؾ�������
vector<Rect> findNumberArea(Mat src, int thresholdVal)
{
	vector<Rect> dstRect;
	Mat dst;

	//ͨ������
	vector<Mat> Vchannels;
	Mat channel_b, channel_g, channel_r;
	split(src, Vchannels);
	channel_b = Vchannels.at(0);
	channel_g = Vchannels.at(1);
	channel_r = Vchannels.at(2);

	channel_r.copyTo(dst);				//��ɫͨ���Աȶ����

	//�ֶ���ֵ��
	threshold(dst, dst, 190, 255, CV_THRESH_BINARY);

	//��ʴ���Ͳ���
	Mat kernel = getStructuringElement(MORPH_RECT, Size(15, 2), Point(-1, -1));	//������κ�
	erode(dst, dst, kernel, Point(-1, -1), 1, 0);
	kernel = getStructuringElement(MORPH_RECT, Size(2, 300), Point(-1, -1));	//������κ�
	dilate(dst, dst, kernel, Point(-1, -1), 1, 0);

	imshow("show", dst);

	return dstRect;
}
