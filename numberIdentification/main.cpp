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

	vector<Rect> numbers0 = findNumberArea(parts[0], 190);
	vector<Rect> numbers1 = findNumberArea(parts[1], 190);
	vector<Rect> numbers2 = findNumberArea(parts[2], 190);
	
	char str[5] = "img0";
	int ii = 0;
	for (auto x : numbers0) {
		str[4] = (ii++) + '0';
		imshow(str, parts[0](x));
	}
	waitKey();

	//imshow("parts0", parts[0]);
	//imshow("parts1", parts[1]);
	//imshow("parts2", parts[2]);
	//imshow("test", src_changeable);

	//printf("%d,%d", stringArea[0].x, stringArea[0].y);

	waitKey(0);
	return 0;
}