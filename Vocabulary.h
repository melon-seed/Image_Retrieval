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
	void setClusterCount(uint count);//�����뱾��С
	void createCodebook(const std::vector<cv::Mat>& descriptorsList);//�����뱾
	void saveCodebook(std::string filename);//�����뱾
	void createKDTree(const cv::Mat centers);//����kdtree

	//
	cv::Mat codebook;//�����뱾

private:
	//
	int clusterCount;
	cv::Mat descriptorsMat;
	std::vector<int> labels;
	
	cv::flann::Index kdTree;
};

