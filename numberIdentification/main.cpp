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
	vector<Mat> parts_changeable(stringArea.size());
	parts.clear();
	for (int i = 0; i < stringArea.size(); i++)
	{
		parts.push_back(separateStringArea(src, stringArea[i]));
		parts[i].copyTo(parts_changeable[i]);
	}
	enhanceStringArea(parts_changeable);

	//寻找单个区域中的单个数字
	vector<vector<Rect>> numbers(parts.size());
	numbers[0] = findNumberArea(parts_changeable[0], 190, Size(10, 2), Size(2, 300));
	numbers[1] = findNumberArea(parts_changeable[1], 155, Size(10, 2), Size(2, 300));
	numbers[2] = findNumberArea(parts_changeable[2], 150, Size(2, 11), Size(2, 300));
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
	
	//分离单个数字，注意：一定要注释掉上方的查看部分，否则会有边框
	vector<Mat> numbersArea0(numbers[0].size());
	vector<Mat> numbersArea1(numbers[1].size());
	vector<Mat> numbersArea2(numbers[2].size());
	numbersArea0 = separateNumberArea(parts[0], numbers[0]);
	numbersArea1 = separateNumberArea(parts[1], numbers[1]);
	numbersArea2 = separateNumberArea(parts[2], numbers[2]);
	//查看
	//char strNum[4] = "2-0";
	//for (int i = 0; i < numbersArea1.size(); i++)
	//{
	//	strNum[2] = (char)(i+'0');
	//	namedWindow(strNum, WINDOW_NORMAL);
	//	imshow(strNum, numbersArea1[i]);
	//}
	//for(int j = 0; j < numbers[1].size(); j++)
	//{
	//	rectangle(parts[1], numbers[1][j], Scalar(CV_RGB(0, 255, 0)), 1, 8, 0);
	//}
	//imshow("part1", parts[1]);


	//imshow("parts0", parts[0]);
	//imshow("parts1", parts[1]);
	//imshow("parts2", parts[2]);
	//imshow("test", src_changeable);
	//printf("%d,%d", stringArea[0].x, stringArea[0].y);

	waitKey(0);
	return 0;
}