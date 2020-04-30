#pragma once


#include "Vocabulary.h"
#include <stddef.h>


class vlad
{
public:
	vlad();
	~vlad();
	//�õ�ѵ����vlad
	void getTrainVLAD(std::vector<cv::Mat>& descriptors, const cv::Mat& codebook, std::vector<cv::Mat>& trainVLAD);
	
	//�õ����Ե�vlad
	void getTestVLAD(std::vector<cv::Mat>& descriptors, const cv::Mat& codebook, std::vector<cv::Mat>& testVLAD);
	
	//����kdtree��������
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

