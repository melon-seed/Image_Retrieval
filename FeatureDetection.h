#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <io.h>

using namespace std;
using namespace cv;

namespace fd
{
	//KAZE
	int kaze(const cv::Mat& srcImg, vector<KeyPoint>& keyPoints, Mat& descriptor);
	//AKAZE
	int akaze(const Mat& srcImg, vector<KeyPoint>& keyPoints, Mat& descriptor);
	//SIFT
	int sift(const Mat& srcImg, vector<KeyPoint>& keyPoints, Mat& descriptor);
	//SURF
	int surf(const Mat& srcImg, vector<KeyPoint>& keyPoints, Mat& descriptor);
	//ORB
	int orb(const Mat& srcImg, vector<KeyPoint>& keyPoints, Mat& descriptor);

	//draw keypoint
	void drawKeypointImage(string name,const Mat& srcImg, vector<KeyPoint>& keyPoint);
	//get files list
	void getFiles(string path, vector<string>& files);
	//
	void getDescriptor(string imagePath, string method, Mat& descriptor);
	void getDescriptors(vector<string> imageFilesList, string method, vector<Mat>& descriptorsList);
	//
	int calHammingDistance(cv::Mat baseImg, cv::Mat targetImg);
	double calEuclideanDistance(cv::Mat baseImg, cv::Mat targetImg);
}
