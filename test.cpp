//计算每一种算法在提取相同特征点所用的时间
#include <iostream>
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <algorithm>
#include "FeatureDetection.h"
#include <time.h>

using namespace std;

/*
int main()
{
	string path = "E:\\1file\\myself\\图像检索算法设计项目\\picture\\TIME";
	vector<string> files;
	clock_t start, finish;
	fd::getFiles(path, files);
	vector<Mat> descriptors;

	//输入使用的方法
	string method = "SIFT";
	cout << "使用的方法：" << method << endl;
	start = clock();
	fd::getDescriptors(files, method, descriptors);
	finish = clock();
	double times = static_cast<double>(finish - start) / CLOCKS_PER_SEC;
	int imgNum = files.size();
	printf("\n");
	std::cout << times / imgNum << std::endl;
	vector<string> quaFiles;
	for (int i = 0; i < descriptors.size(); ++i)
	{
		//std::cout << descriptors.at(i).rows << std::endl;
		if ((descriptors.at(i).rows > 295) & (descriptors.at(i).rows < 305))
		{
			std::cout << "OK: " << descriptors.at(i).rows << std::endl;
			std::cout << files.at(i) << std::endl;
			quaFiles.push_back(files.at(i));
		}
	}
	vector<Mat> quaDescriptors;
	start = clock();
	fd::getDescriptors(quaFiles, method, quaDescriptors);
	finish = clock();
	double quatimes = static_cast<double>(finish - start) / CLOCKS_PER_SEC;
	printf("\n");
	std::cout << "avg time: " << 1000 * (quatimes / quaFiles.size()) << std::endl;

}
*/
