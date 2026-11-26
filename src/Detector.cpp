#include"Detector.hpp"
#include"pnp_solver.hpp"
#include<opencv2/opencv.hpp>
#include<bits/stdc++.h>
#include<opencv2/aruco.hpp>
#include<vector>

using namespace std;
using namespace cv;

void Detector::detect(cv::Mat& img,std::vector<std::vector<cv::Point2f>>& corners)

{
    auto dictionary = aruco::getPredefinedDictionary(aruco::DICT_APRILTAG_36h11);//选择编码字典
    
    vector<int> ids;//存储编号                 
    //vector<vector<Point2f>> corners; //存储角点 

    aruco::detectMarkers(img, dictionary, corners, ids);//输出角点和编号
    aruco::drawDetectedMarkers(img,corners,ids);//绘制编号，角点和边框
}