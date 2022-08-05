#pragma once
#include<opencv2/opencv.hpp>
#include<vector>
#include<string>
#include<iostream>

class Cam{
    private:
        
    public:
        cv::Mat InitImg;
        cv::Mat AdjustedImg;
        cv::Mat cameraMatrix = cv::Mat::eye(3, 3, CV_64F);
        cv::Mat distCoeffs = cv::Mat::zeros(5, 1, CV_64F);
        void Cam_Init();
        bool getImage();
        void imgAdjust();
};