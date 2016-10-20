#include"header.h"

//ͼ��Ԥ������
vector<Mat> preProcess(Mat src, vector<Mat> result)
{
	result.clear();
	Mat src_changeable;
	src.copyTo(src_changeable);
	Mat dst,temp_mask;
	//ͨ������
	vector<Mat> Vchannels;
	Mat channel_b, channel_g, channel_r;
	split(src,Vchannels);
	channel_b = Vchannels.at(0);
	channel_g = Vchannels.at(1);
	channel_r = Vchannels.at(2);

	channel_r.copyTo(dst);				//��ɫͨ���Աȶ����

	//addWeighted(channel_g, 0.5, channel_r, 0.5, 0, temp);

	//������˹�����񻯣�Ч�����ã�����
	//Mat sharpenKernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	//filter2D(dst, dst, dst.depth(), sharpenKernel);

	//�������񻯣�Ч������ȥ�������
	//Mat mask;
	//GaussianBlur(dst, mask, Size(17, 17), 0, 0);
	//mask = dst - mask;
	//dst = dst + mask * 4;

	//ȫ����ֵ����Ч�����ã�����
	//adaptiveThreshold(temp, dst, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, 0);

	//�ֶ���ֵ��
	threshold(dst, dst, 155, 255, CV_THRESH_BINARY);

	//��һ������
	//Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));	//���κ�
	//Mat kernel = getStructuringElement(MORPH_CROSS, Size(7, 7), Point(-1, -1));	//ʮ�ֺ�
	Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(7, 7), Point(-1, -1));	//Բ�ˣ�Ч���Ϻ�
	erode(dst, dst, kernel, Point(-1, -1), 1, 0);
	dilate(dst, dst, kernel, Point(-1, -1), 1, 0);
	dilate(dst, dst, kernel, Point(-1, -1), 1, 0);
	erode(dst, dst, kernel, Point(-1, -1), 1, 0);


	/******************************************************************************/
	/*******************������ֵ����Ч������,���������Ƿֿ�����***************************/
	/******************************************************************************/

	//�������ִ��õ�ģ��
	boxFilter(dst, temp_mask, -1, Size(81,81));
	threshold(temp_mask, temp_mask, 20, 255, CV_THRESH_BINARY);
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
		rectangle(src_changeable, boundRect[i], Scalar(CV_RGB(255,0,0)), 2, 8, 0);
		result.push_back(channel_r(Rect(boundRect[i])));
	}
	imshow("��⵽����������", src_changeable);


	//���ֲ��ֱַ���
	threshold(result[0], result[0], 148, 255, CV_THRESH_BINARY);
	kernel = getStructuringElement(MORPH_ELLIPSE, Size(5, 5), Point(-1, -1));	//Բ�ˣ�Ч���Ϻ�
	erode(result[0], result[0], kernel, Point(-1, -1), 1, 0);
	dilate(result[0], result[0], kernel, Point(-1, -1), 1, 0);
	dilate(result[0], result[0], kernel, Point(-1, -1), 1, 0);
	erode(result[0], result[0], kernel, Point(-1, -1), 1, 0);




	return result;
}