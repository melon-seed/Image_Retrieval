#include "Vocabulary.h"



Vocabulary::Vocabulary()
{
	this->clusterCount =128;//设置不同码本大小的参数
	printf("码本大小128\n");
}

Vocabulary::~Vocabulary()
{

}

void Vocabulary::setClusterCount(uint count)
{
	this->clusterCount = count;
}

void Vocabulary::createCodebook(const std::vector<cv::Mat>& descriptorsList)
{
	cv::vconcat(descriptorsList, descriptorsMat);
	/*for (int i = 0; i < descriptorsList.size(); ++i)
	{
		cv::vconcat(descriptorsMat, descriptorsList.at(i), descriptorsMat);
	}*/
	//descriptorsMat.convertTo(descriptorsMat, CV_32F);

	printf("执行完成数据转换cv_32f\n");
	cv::kmeans(descriptorsMat, this->clusterCount, this->labels,
		cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 100, 0.01), 3, cv::KMEANS_PP_CENTERS, this->codebook);
	
}

void Vocabulary::saveCodebook(std::string filename)
{
	cv::FileStorage fs(filename, cv::FileStorage::WRITE);
	fs << "Codebook" << codebook;
	fs.release();
}

void Vocabulary::createKDTree(const cv::Mat centers)
{
	kdTree.build(centers, cv::flann::KDTreeIndexParams(1));
	kdTree.save("kdtree.mat");
	cv::FileStorage fs("tree.yml", cv::FileStorage::WRITE);
	fs << "kdtree" << centers;
	fs.release();
}


