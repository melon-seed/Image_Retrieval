//
//
#include "FeatureDetection.h"

int fd::kaze(const Mat& srcImg, vector<KeyPoint>& keyPoints, Mat& descriptor)
{
	if (srcImg.empty())
	{
		return -1;
	}
	Ptr<KAZE> detector = KAZE::create();
	detector->detectAndCompute(srcImg, Mat(), keyPoints, descriptor);

	//cout << descriptor;

	return 1;
}

int fd::akaze(const Mat& srcImg, vector<KeyPoint>& keyPoints, Mat& descriptor)
{
	if (srcImg.empty())
	{
		return -1;
	}
	Ptr<AKAZE> detector = AKAZE::create();
	detector->detectAndCompute(srcImg, Mat(), keyPoints, descriptor);
	return 1;
}

int fd::sift(const Mat& srcImg, vector<KeyPoint>& keyPoints, Mat& descriptor)
{
	if (srcImg.empty())
	{
		return -1;
	}
	Ptr<xfeatures2d::SiftFeatureDetector>detector = cv::xfeatures2d::SIFT::create();
	detector->detectAndCompute(srcImg, Mat(), keyPoints, descriptor);
	return 1;
}

int fd::surf(const Mat& srcImg, vector<KeyPoint>& keyPoints, Mat& descriptor)
{
	if (srcImg.empty())
	{
		return -1;
	}
	Ptr<xfeatures2d::SurfFeatureDetector>detector = cv::xfeatures2d::SURF::create();
	detector->detectAndCompute(srcImg, Mat(), keyPoints, descriptor);
	return 1;
}

int fd::orb(const Mat& srcImg, vector<KeyPoint>& keyPoints, Mat& descriptor)
{
	if (srcImg.empty())
	{
		return -1;
	}
	Ptr<ORB> detector = ORB::create();
	detector->detectAndCompute(srcImg, Mat(), keyPoints, descriptor);
	return 1;
}



void fd::drawKeypointImage(string name, const Mat& srcImg, vector<KeyPoint>& keyPoint)
{
	string imageName = name + " keypoint";
	Mat keyPointsImg;
	drawKeypoints(srcImg, keyPoint, keyPointsImg, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	imshow(imageName, keyPointsImg);
	waitKey(0);
}

void fd::getFiles(string path, vector<string>& files)
{
	//文件句柄  
	intptr_t   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

void fd::getDescriptor(string imagePath, string method, Mat& descriptor)
{
	


	Mat img = imread(imagePath);
	vector<KeyPoint> keypoints;
	if (method == "KAZE")
	{
		kaze(img, keypoints, descriptor);
	}
	else if(method == "AKAZE")
	{
		akaze(img, keypoints, descriptor);
	}
	else if (method == "SIFT")
	{
		sift(img, keypoints, descriptor);
	}
	else if (method == "SURF")
	{
		surf(img, keypoints, descriptor);
	}
	else if (method == "ORB")
	{
		orb(img, keypoints, descriptor);
	}

}

void fd::getDescriptors(vector<string> imageFilesList, string method, vector<Mat>& descriptorsList)
{
	int i;
	int imageFileLength = imageFilesList.size();
	for (i = 0; i < imageFileLength; ++i)
	{
		printf("\rProcessing the %d image. Have proecssed: %2d %%", i, (i * 100 / imageFileLength) + 1);
		fflush(stdout);
		Mat descriptor;
		getDescriptor(imageFilesList.at(i), method, descriptor);
		descriptorsList.push_back(descriptor);
	}


}


//没有用到汉明距离
int fd::calHammingDistance(cv::Mat baseImg, cv::Mat targetImg)
{
	baseImg.convertTo(baseImg, CV_8U);
	targetImg.convertTo(targetImg, CV_8U);
	int distance = 0;
	for (int i = 0; i < baseImg.cols; ++i)
	{
		int base = baseImg.at<uchar>(0, i);
		int target = targetImg.at<uchar>(0, i);
		std::cout << "base: " << base << " target: " << target << std::endl;
		if (base != target)
		{
			distance++;
		}
	}
	return distance;
}

//使用欧氏距离计算
double fd::calEuclideanDistance(cv::Mat baseImg, cv::Mat targetImg)
{
	cv::Mat difference;
	cv::subtract(baseImg, targetImg, difference);
	double distance = cv::norm(difference);
	return distance;
}
