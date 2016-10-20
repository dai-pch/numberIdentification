#include "header.h"
#include "function.h"

extern Mat src;

int main()
{
	Mat dst = preProcess(src);

	imshow("test",dst);
	waitKey(0);
	return 0;
}