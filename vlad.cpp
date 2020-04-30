#include "vlad.h"

vlad::vlad()
{

}

vlad::~vlad()
{

}

void vlad::getTrainVLAD(std::vector<cv::Mat>& descriptors, const cv::Mat& codebook, std::vector<cv::Mat>& trainVLAD)
{
	int codebookSize = codebook.rows;
	for (int i = 0; i < descriptors.size(); ++i)
	{
		cv::Mat descriptor = descriptors.at(i);
		//std::cout << "size: " << descriptor.rows << " " << descriptor.cols << std::endl;
		trainVLAD.push_back(calImgVLAD(descriptors.at(i), codebook));
	}
}

void vlad::getTestVLAD(std::vector<cv::Mat>& descriptors, const cv::Mat& codebook, std::vector<cv::Mat>& testVLAD)
{
	for (int i = 0; i < descriptors.size(); ++i)
	{
		testVLAD.push_back(calImgVLAD(descriptors.at(i), codebook));
	}
}

cv::Mat vlad::getImgVLAD(const cv::Mat& descriptor, const cv::Mat& codebook)
{
	int codebookSize = codebook.rows;
	int size = descriptor.cols;
	std::vector<cv::Mat> vladBitMatrix;
	std::vector<cv::Mat> vladMatrix;
	for (int i = 0; i < codebookSize; ++i)
	{
		cv::Mat Z = cv::Mat::zeros(1, size * sizeof(uint8_t) * 8, CV_32FC1);
		cv::Mat X = cv::Mat::zeros(1, size * sizeof(uint8_t) * 8, CV_8U);
		vladBitMatrix.push_back(Z);
		vladMatrix.push_back(X);
	}
	//
	int sum = 0;
	std::vector<int> indices;
	std::cout << "descriptor: " << descriptor.rows << " " << descriptor.cols << std::endl;
	getWordIdAndCenters(descriptor, indices);
	std::cout << indices.size() << std::endl;
	for (int i = 0; i < descriptor.rows; ++i)
	{
		cv::Mat A = descriptor(cv::Rect(0, i, descriptor.cols, 1));
		int wordId = indices.at(i);
		int bitCur = 0;
		std::cout << wordId << std::endl;
		for (int j = 0; j < A.cols; ++j)
		{
			std::cout << "hee" << std::endl;
			A.convertTo(A, CV_8U);
			uint8_t a = A.at<uint8_t>(0, j);
			std::cout << "hee" << std::endl;
			codebook.convertTo(codebook, CV_8U);
			uint8_t cen = codebook.at<uint8_t>(0, j);
			std::cout << "hee" << std::endl;
			uint8_t temp = a ^ cen;
			uint8_t mask = 0x01;
			for (int k = 0; k < 8; ++k)
			{
				if (temp & mask)
				{
					vladBitMatrix[wordId].at<float>(0, bitCur)++;
					bitCur++;
					sum++;
				}
				else
				{
					bitCur++;
				}
				mask = mask << 1;
			}
		}

	}
	float thr = static_cast<float>(sum) / (codebookSize * size * 8.0f);
	for (int j = 0; j < codebookSize; ++j)
	{
		int bitCur = 0;
		for (int k = 0; k < size; ++k)
		{
			for (int l = 0; l < 8; ++l)
			{
				if (vladBitMatrix[j].at<uint8_t>(0, bitCur) > thr)
				{
					vladMatrix[j].at<uint8_t>(0, bitCur) = 1;
				}
				bitCur++;
			}
		}
	}
	cv::Mat vlad = cv::Mat::zeros(1, 0, CV_8U);
	for (int j = 0; j < codebookSize; ++j)
	{
		cv::hconcat(vladMatrix[j], vlad, vlad);
	}
	return vlad;
}

cv::Mat vlad::calImgVLAD(const cv::Mat& descriptor, const cv::Mat& codebook)
{
	int codebookSize = codebook.rows;
	int size = descriptor.cols;
	std::vector<cv::Mat> vladMatrix;
	for (int i = 0; i < codebookSize; ++i)
	{
		cv::Mat Z = cv::Mat::zeros(1, size, CV_32FC1);
		vladMatrix.push_back(Z);
	}
	std::vector<int> indices;
	getWordIdAndCenters(descriptor, indices);
	for (int j = 0; j < descriptor.rows; ++j)
	{
		cv::Mat A = descriptor(cv::Rect(0, j, size, 1));
		int wordId = indices.at(j);
		cv::Mat central = codebook(cv::Rect(0, wordId, size, 1));
		cv::Mat tempA, tempCentral;
		A.convertTo(tempA, CV_32FC1);
		central.convertTo(tempCentral, CV_32FC1);
		vladMatrix[wordId] += (tempA - tempCentral);
	}
	cv::Mat vlad = cv::Mat::zeros(1, 0, CV_32FC1);
	for (int j = 0; j < codebookSize; ++j)
	{
		cv::hconcat(vladMatrix[j], vlad, vlad);
	}
	cv::Mat vladNorm;
	vlad.copyTo(vladNorm);
	cv::normalize(vlad, vladNorm, 1, 0, cv::NORM_L2);
	return vladNorm;
}

void vlad::loadKDTree(std::string filename)
{

}

void vlad::createKDTree(const cv::Mat& codebook)
{
	codebook.convertTo(codebook, CV_32F);
	std::cout << "codebook: " << codebook.rows << " " << codebook.cols << std::endl;
	Kdtree.build(codebook, cv::flann::KDTreeIndexParams(1));
}

void vlad::getWordIdAndCenters(const cv::Mat& query, std::vector<int>& indices)
{
	std::vector<float> dists;
	std::vector<int> vecIndex;
	query.convertTo(query, CV_32F);
	for (int i = 0; i < query.rows; ++i)
	{
		std::vector<int> indiex;
		Kdtree.knnSearch(query.row(i), indiex, dists, 1, cv::flann::SearchParams(-1));
		for (int j = 0; j < indiex.size(); ++j)
		{
			indices.push_back(indiex.at(j));
		}
	}
}

