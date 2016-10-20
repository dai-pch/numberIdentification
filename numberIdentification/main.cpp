#include "header.h"
#include "function.h"

//extern Mat src;

int main()
{
	
	static Mat src = imread("./img/src.jpg");
	Mat src_changeable;
	src.copyTo(src_changeable);

	//查找区域
	vector<Rect> stringArea = findStringArea(src);
	//从上到下序号排序
	stringArea = sortStringArea(stringArea);
	//查看找到的区域
	for (int i = 0; i < stringArea.size(); i++)
		rectangle(src_changeable, stringArea[i], Scalar(CV_RGB(255, 0, 0)), 2, 8, 0);

	//分离区域
	vector<Mat> parts;
	parts.clear();
	for (int i = 0; i < stringArea.size(); i++)
		parts.push_back(separateStringArea(src, stringArea[i]));
	Mat shadow = Mat(Size(parts[1].cols - 450, parts[1].rows),parts[1].type(),Scalar(CV_RGB(0,0,0)));
	addWeighted(shadow,0.17,parts[1](Rect(450, 0,parts[1].cols-450,parts[1].rows)),0.83,
		0, parts[1](Rect(450, 0, parts[1].cols - 450, parts[1].rows)));

	//寻找单个区域中的单个数字
	vector<vector<Rect>> numbers(parts.size());
	//numbers[0] = findNumberArea(parts[0], 190, Size(10, 2), Size(2, 300));
	numbers[1] = findNumberArea(parts[1], 155, Size(10, 2), Size(2, 300));

	//查看
	//char str[6] = "test0";
	//for (int i = 0; i < numbers.size(); i++)
	//{
	//	for(int j = 0; j < numbers[i].size(); j++)
	//	{
	//		rectangle(parts[i], numbers[i][j], Scalar(CV_RGB(0, 255, 0)), 1, 8, 0);
	//	}
	//	str[4] = (char)(i + '0');
	//	imshow(str, parts[i]);
	//}
	

	//imshow("parts0", parts[0]);
	//imshow("parts1", parts[1]);
	//imshow("parts2", parts[2]);
	//imshow("test", src_changeable);
	

	//printf("%d,%d", stringArea[0].x, stringArea[0].y);

	waitKey(0);
	return 0;
}