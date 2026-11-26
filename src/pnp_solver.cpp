#include"Detector.hpp"
#include"pnp_solver.hpp"
#include<bits/stdc++.h>
#include<opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

bool pnpSolve(   const std::vector<cv::Point3f>&objectPoints,
    const std::vector<cv::Point2f>&imagePoints,
    const cv::Mat& K,
    const cv::Mat& distCoeffs,
    cv::Mat& rvec,
    cv::Mat& tvec
)
{
    
    //PnP 参数留在main里给投影的时候用
    return solvePnP(objectPoints,imagePoints,K,distCoeffs,rvec,tvec);



}