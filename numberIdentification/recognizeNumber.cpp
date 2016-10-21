#include"header.h"

double relativity(const Mat img, const Mat module) {
	return 1;
}

char recognize(const Mat src, const vector<Mat> modules, const int thre) {
	CV_DbgAssert(src.rows == 120 && src.cols == 60);
	Mat dst;
	cvtColor(src, dst, COLOR_BGR2GRAY);
	threshold(dst, dst, 60, 255, CV_THRESH_BINARY);
	imshow("recog", dst);
	waitKey();
	vector<double> rel;
	for (auto x : modules) {
		rel.push_back(relativity(dst, x));
	}
	
	double max = 0;
	char res=0;
	for (int ii = 0;ii < rel.size();++ii) {
		if (rel[ii] > max) {
			res = '0' + ii;
			max = rel[ii];
		}
	}
	return res;
}

vector<char> recognizeNubmers(const vector<Mat> srcList, const vector<Mat> modules, const int thre) {
	vector<char> res;
	for (auto x : srcList) 
		res.push_back(recognize(x, modules, thre));
	return res;
}