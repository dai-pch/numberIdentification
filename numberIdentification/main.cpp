#include "header.h"
#include "function.h"

//extern Mat src;

int main()
{
	
	vector<Mat> parts;
	static Mat src = imread("./img/src.jpg");
	Mat src_changeable;
	src.copyTo(src_changeable);

	vector<Rect> stringArea = findStringArea(src);
	//查看找到的区域
	for (int i = 0; i < stringArea.size(); i++)
		rectangle(src_changeable, stringArea[i], Scalar(CV_RGB(255, 0, 0)), 2, 8, 0);



	//parts = preProcess(src, parts);

	imshow("test", src_changeable);
	waitKey(0);
	return 0;
}