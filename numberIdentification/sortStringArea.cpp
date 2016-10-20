#include"header.h"

//对数字串区域排序，按照从上到下
vector<Rect> sortStringArea(vector<Rect> srcRect)
{
	Rect temp;
	//冒泡
	int i = 0, j = 0;
	for (i = 0; i < srcRect.size() - 1; i++)
	{
		for (j = 1; j < srcRect.size(); j++)
		{
			if (srcRect[i].y > srcRect[j].y)
			{
				temp = srcRect[i];
				srcRect[i] = srcRect[j];
				srcRect[j] = temp;
			}
		}
	}
	return srcRect;
}
