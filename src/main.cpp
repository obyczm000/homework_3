#include"Detector.hpp"
#include"pnp_solver.hpp"
#include<opencv2/opencv.hpp>
#include<bits/stdc++.h>

using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap(0);
    Mat img,gray,binary,rvec,tvec;
    Detector detect;
    vector<vector<Point2f>> corners;
    vector<Point3f> objectPoints;



    Mat K=(Mat_<double>(3,3)<<
        594.327292414465, 0.0, 303.4293433502377, 
        0.0, 593.9942594975369, 246.84703791449914, 
        0.0, 0.0, 1.0);

    
    Mat distCoeffs=(Mat_<double>(1,5)<<
        0.03501562340842385, -0.09628732084605696, 0.006094720963224223, -0.002502128055514398, 0.0);
    

    //世界坐标点
    objectPoints.push_back(Point3f(0.0f, 0.0f, 0.0f));
    objectPoints.push_back(Point3f(0.05f, 0.0f, 0.0f));
    objectPoints.push_back(Point3f(0.05f, 0.05f, 0.0f));
    objectPoints.push_back(Point3f(0.0f, 0.05f, 0.0f));

   
    vector<Point3f> cubePoints = objectPoints;//复制一份给投影
    cubePoints.push_back(Point3f(0.0f, 0.0f, -0.05f));
    cubePoints.push_back(Point3f(0.05f, 0.0f, -0.05f));
    cubePoints.push_back(Point3f(0.05f, 0.05f, -0.05f));
    cubePoints.push_back(Point3f(0.0f, 0.05f, -0.05f));

    while(true)
    {
        cap.read(img);
        //二值化
        cvtColor(img,gray,COLOR_BGR2GRAY);
        threshold(gray,binary,127,255,THRESH_BINARY);
        detect.detect(img,corners);
        if(!corners.empty())
        {
            //求解外参
            bool success=pnpSolve(objectPoints,corners[0],K,distCoeffs,rvec,tvec);
            if (!success) 
            {
            cout << "PnP failed!" << endl;
            }
            else
            {
            cout << "Rotation vector (rvec):\n" << rvec << endl;
            cout << "Translation vector (tvec):\n" << tvec << endl;

            

            //投影
            vector<Point2f> projectedPoints;
            projectPoints(cubePoints, rvec, tvec, K, distCoeffs, projectedPoints);
                cout << "Reprojected points:" <<endl;
                for (size_t i = 0; i < projectedPoints.size(); i++)
                {
                cout << projectedPoints[i] << endl;//输出角点坐标
                //画顶点
                circle(img,projectedPoints[i],4,Scalar(0,255,0),-1);
                }
                //画各个面
                for(size_t i=0;i<=3;i++)
                {
                    //底面
                    line(img,projectedPoints[i],projectedPoints[(i+1)%4],Scalar(0,255,0),2);
                    //顶面底面连接
                    line(img,projectedPoints[i+4],projectedPoints[(i+1)%4+4],Scalar(0,255,0),2);
                    //侧棱
                    line(img,projectedPoints[i],projectedPoints[i+4],Scalar(0,255,0),2);

                }
                

            }
        }
        imshow("Image_raw",img);
        imshow("Image_binary",binary);
        waitKey(1);
    }
    return 0;
}