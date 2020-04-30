#pragma once
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <iostream>
class Vocabulary
{
public:
	//
	Vocabulary();
	~Vocabulary();
	void setClusterCount(uint count);//设置码本大小
	void createCodebook(const std::vector<cv::Mat>& descriptorsList);//创建码本
	void saveCodebook(std::string filename);//保存码本
	void createKDTree(const cv::Mat centers);//创建kdtree

	//
	cv::Mat codebook;//此乃码本

private:
	//
	int clusterCount;
	cv::Mat descriptorsMat;
	std::vector<int> labels;
	
	cv::flann::Index kdTree;
};

