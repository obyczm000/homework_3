#include<opencv2/opencv.hpp>
#include<vector>

class Detector
{

public:
    void detect(cv::Mat& img,std::vector<std::vector<cv::Point2f>>& corners);
};

