#pragma once


#include "Vocabulary.h"
#include <stddef.h>


class vlad
{
public:
	vlad();
	~vlad();
	//得到训练的vlad
	void getTrainVLAD(std::vector<cv::Mat>& descriptors, const cv::Mat& codebook, std::vector<cv::Mat>& trainVLAD);
	
	//得到测试的vlad
	void getTestVLAD(std::vector<cv::Mat>& descriptors, const cv::Mat& codebook, std::vector<cv::Mat>& testVLAD);
	
	//创建kdtree，搜索树
	void createKDTree(const cv::Mat& codebook);


private:
	//
	cv::flann::Index Kdtree;
	//
	cv::Mat getImgVLAD(const cv::Mat& descriptor, const cv::Mat& codebook);
	cv::Mat calImgVLAD(const cv::Mat& descriptor, const cv::Mat& codebook);
	void loadKDTree(std::string filename);
	
	void getWordIdAndCenters(const cv::Mat& query, std::vector<int>& indices);
	
};

