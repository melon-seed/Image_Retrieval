// cv.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//主要查准率、查全率的main文件
#include <iostream>
#include <opencv2/opencv.hpp>
#include "FeatureDetection.h"
#include <time.h>
#include "Vocabulary.h"
#include "vlad.h"
#include <algorithm>


int main()
{
    std::vector<std::string> fileList;
    
    //训练集路径
    char path[] = "E:\\1file\\myself\\图像检索算法设计项目\\picture\\Train";
    fd::getFiles(path, fileList);
    std::vector<Mat> descriptors;
    std::cout << "get train descriptors" << std::endl;

    //输入所要使用的方法
    string method = "AKAZE";                 
    cout << "使用的方法：" << method << endl;
    fd::getDescriptors(fileList, method, descriptors);//得到文件夹下所有图片的描述子
    printf("\n");

    Vocabulary voc;//用来创建码书的
    std::cout << "Creat codebook....." << std::endl;
    voc.createCodebook(descriptors);//创建码书
    voc.saveCodebook("E:\\codebook.cb");//保存码书

    vlad vd;//用来生成vlad的，测试集与训练集的vlad
    std::vector<cv::Mat> vladBase;//
    std::cout << "Creat KD-Tree...." << std::endl;
    vd.createKDTree(voc.codebook);
    std::cout << "Get Train vlad...." << std::endl;
    vd.getTrainVLAD(descriptors, voc.codebook, vladBase);

    //测试集路径
    char testPath[] = "E:\\1file\\myself\\图像检索算法设计项目\\picture\\Test";
    std::vector<std::string> testFileList;
    fd::getFiles(testPath, testFileList);
    std::vector<Mat> testDescriptors;
    std::cout << "Get test descriptors...." << std::endl;
    fd::getDescriptors(testFileList, method, testDescriptors);
    printf("\n");
    std::vector<cv::Mat> vladTest;
    vd.getTestVLAD(testDescriptors, voc.codebook, vladTest);

    //测试集的vlad与训练集的vlad做比对，检索步骤
    std::vector<std::vector<pair<double, int>>> pairsLists;
    for (int i = 0; i < vladTest.size(); ++i)
    {
        std::vector<pair<double, int>> pairs;
        for (int j = 0; j < vladBase.size(); ++j)
        {
            double dis = fd::calEuclideanDistance(vladBase[j], vladTest[i]);
            //std::cout << "dis: " << dis << std::endl;
            //std::cout << "file: " << fileList.at(j) << std::endl;
            pairs.push_back(make_pair(dis, j));
        }
        sort(pairs.begin(), pairs.end());
        pairsLists.push_back(pairs);
    }
    vector<string> nameList;
    nameList.push_back("化妆");
    nameList.push_back("树叶");
    nameList.push_back("水滴");

    //输出查全率与查准率
    for (int i = 0; i < pairsLists.size(); ++i)
    {
        int m = 0;
        int p = 0;
        for (int j = 0; j < 10; ++j)
        {
            int index = pairsLists.at(i).at(j).second;
            int inx = fileList.at(index).find(nameList.at(i));
            if (inx == string::npos)
            {
                p++;
            }
            else
            {
                m++;
            }
        }
        int temp = m + p;
        std::cout << nameList.at(i) << std::endl;
        std::cout << "查全率：" << static_cast<double>(m) / static_cast<double>(16) << std::endl;
        std::cout << "查准率：" << static_cast<double>(m) / static_cast<double>(temp) << std::endl;
    }
}

