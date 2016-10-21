#include"header.h"

//����������ͼƬ
vector<Mat> numberProcess(vector<Mat> src)
{
	vector<Mat> dst;
	for (int i = 0; i < src.size(); i++)
	{
		Mat temp;
		//ͨ������
		vector<Mat> Vchannels;
		Mat channel_b, channel_g, channel_r;
		split(src[i], Vchannels);
		channel_b = Vchannels.at(0);
		channel_g = Vchannels.at(1);
		channel_r = Vchannels.at(2);
		channel_r.copyTo(temp);				//��ɫͨ���Աȶ����
		//src[i].copyTo(temp);
		//cvtColor(temp, temp, CV_RGB2GRAY);

		adaptiveThreshold(temp, temp, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 121, -45);

		Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(6, 6), Point(-1, -1));
		erode(temp, temp, kernel, Point(-1, -1), 1, 0);
		dilate(temp, temp, kernel, Point(-1, -1), 1, 0);
		dilate(temp, temp, kernel, Point(-1, -1), 1, 0);
		erode(temp, temp, kernel, Point(-1, -1), 1, 0);
		dst.push_back(temp);
	}
	return dst;
}