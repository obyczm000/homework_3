#include<opencv2/opencv.hpp>
#include<vector>

bool pnpSolve
(
    const std::vector<cv::Point3f>&objectPoints,
    const std::vector<cv::Point2f>&imagePoints,
    const cv::Mat& K,
    const cv::Mat& distCoeffs,
    cv::Mat& rvec,
    cv::Mat& tvec
);