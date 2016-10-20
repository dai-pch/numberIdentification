#include "header.h"
#include "function.h"

extern Mat src;

int main()
{
	vector<Mat> parts;
	parts = preProcess(src, parts);

	//imshow("test",dst);
	waitKey(0);
	return 0;
}