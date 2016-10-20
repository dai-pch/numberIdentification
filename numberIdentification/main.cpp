#include "header.h"
#include "function.h"

//extern Mat src;

int main()
{
	
	static Mat src = imread("./img/src.jpg");
	Mat src_changeable;
	src.copyTo(src_changeable);

	vector<Rect> stringArea = findStringArea(src);
	//查看找到的区域
	for (int i = 0; i < stringArea.size(); i++)
		rectangle(src_changeable, stringArea[i], Scalar(CV_RGB(255, 0, 0)), 2, 8, 0);

	vector<Mat> parts;
	parts.clear();
	for (int i = 0; i < stringArea.size(); i++)
		parts.push_back(separateStringArea(src, stringArea[i]));
	

	imshow("parts0", parts[0]);
	imshow("parts1", parts[1]);
	imshow("parts2", parts[2]);
	imshow("test", src_changeable);
	waitKey(0);
	return 0;
}