#include"header.h"
#include<string>

//拟对parts[1]中数字进行切割并储存作为之后的匹配模板
void cutAndSave(Mat part, vector<Rect> numberRect)
{
	int i = 0;
	string str;
	Mat area_temp;
	for (i = 0; i < numberRect.size(); i++)
	{
		part(Rect(numberRect[i])).copyTo(area_temp);
		ostringstream a;
		a << "./img/" << "part1_" << i <<".jpg";
		imwrite(a.str().c_str(), area_temp);
	}
}