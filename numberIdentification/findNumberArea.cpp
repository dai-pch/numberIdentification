#include"header.h"

//对比度拉伸
Mat ContrastStretch(Mat const SourceImage, double min) {
	Mat hist;
	int histSize = 256;
	calcHist(&SourceImage, 1, 0, Mat(), hist, 1, &histSize, 0);
	//cout << hist << endl;

	int data_min = 0, data_max = 255;
	int accumulate = 0, minValue = static_cast<int>(SourceImage.rows * SourceImage.cols * min);
	for (accumulate = 0; data_min < histSize; data_min++) {
		accumulate += (hist.at<float>(data_min));
		if (accumulate > minValue) break;
	}
	
	for (accumulate = 0; data_max >= 0; data_max--) {
		accumulate += hist.at<float>(data_max);
		if (accumulate > minValue) break;
	}

	//cout << data_min << " " << data_max << endl;

	Mat lookUp(1, 256, CV_8U);
	int len = data_max - data_min;

	if (len < 1) return SourceImage;

	for (int i = 0; i < 256; i++) {
		if (i < data_min) lookUp.at<uchar>(i) = 0;
		else if (i > data_max) lookUp.at<uchar>(i) = 255;
		else lookUp.at<uchar>(i) = static_cast<uchar>(255.0*(i - data_min) / len);
	}

	Mat resultImage;
	LUT(SourceImage, lookUp, resultImage);
	return resultImage;
}

//寻找数字串中单个数字的区域范围，返回矩形轮廓
vector<Rect> findNumberArea(Mat src, int thresholdVal)
{
	vector<Rect> dstRect;
	Mat dst, dst2;

	//通道分离
	vector<Mat> Vchannels;
	Mat channel_b, channel_g, channel_r;
	split(src, Vchannels);
	channel_b = Vchannels.at(0);
	channel_g = Vchannels.at(1);
	channel_r = Vchannels.at(2);

	channel_r.copyTo(dst);				//红色通道对比度最高

	//中值滤波
	medianBlur(dst, dst, 9);
	//形态学底帽均匀背景
	int eigenlen = dst.rows;
	morphologyEx(dst, dst, MORPH_BLACKHAT, getStructuringElement(MORPH_RECT, Size(eigenlen, eigenlen)));

	//灰度拉伸
	dst = ContrastStretch(dst, 0.05);
	//手动阈值化
	//threshold(dst, dst2, 65, 255, CV_THRESH_BINARY);
	adaptiveThreshold(dst, dst, 255, ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, 2 * (eigenlen/8) + 1, 10);

	//膨胀
	erode(dst, dst, getStructuringElement(MORPH_ELLIPSE, Size(eigenlen / 16, eigenlen / 8)));


	const int high = 50;
	vector<unsigned char> horizonProjection(static_cast<size_t>(dst.cols));
	Mat hor(high, dst.cols ,CV_8UC1);
	for (int ii = 0; ii < dst.cols; ii++) {
		int sum = 0;
		for (int jj = 0;jj < dst.rows;jj++) {
			sum += dst.at<unsigned char>(Point(ii, jj));
		}
		hor(Rect(ii,0,1, high)) = sum/dst.rows;
		horizonProjection[ii] = sum / dst.rows;
	}
	hor = ContrastStretch(hor, 0.05);
	//cout << hor;

	//切分
	vector<unsigned int>posi;
	unsigned int begin;
	for (int ii = 0;ii < horizonProjection.size();) {
		begin = ii;
		while (horizonProjection[ii] < 5)
			++ii;
		posi.push_back((begin + ii) / 2);
		while (horizonProjection[ii] > 0)
			++ii;
	}

	for (int ii = 1;ii < posi.size();++ii) {
		dstRect.push_back(Rect(Point(posi[ii - 1], 0), Point(posi[ii], dst.rows)));
	}

	imshow("show", dst);
	imshow("pro", hor);
	waitKey();

	return dstRect;
}
