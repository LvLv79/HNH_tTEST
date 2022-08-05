#include "Camera.hpp"

cv::VideoCapture inputVideo("../../1.avi");
void Cam::Cam_Init()
{
    cameraMatrix.at<double>(0, 0) = 1.1527e+03;
    cameraMatrix.at<double>(0, 1) = 0;
    cameraMatrix.at<double>(0, 2) = 618.6327;
    cameraMatrix.at<double>(1, 1) = 1.1527e+03;
    cameraMatrix.at<double>(1, 2) = 361.1508;

    distCoeffs.at<double>(0, 0) = 0.0741;
    distCoeffs.at<double>(1, 0) = -0.0685;
    distCoeffs.at<double>(2, 0) = 0;
    distCoeffs.at<double>(3, 0) = 0;
    distCoeffs.at<double>(4, 0) = 0;
    return;
}

bool Cam::getImage()
{
    if (!inputVideo.isOpened())
    {
        std::cout << "Could not open the input video: " << std::endl;
        return false;
    }
    else
    {
        inputVideo.read(InitImg);
        return true;
    }
}
void Cam::imgAdjust()
{
    cv::Mat map1, map2;
    cv::Size imageSize;
    imageSize = InitImg.size();
    initUndistortRectifyMap(cameraMatrix, distCoeffs, cv::Mat(),
                            getOptimalNewCameraMatrix(cameraMatrix, distCoeffs, imageSize, 1, imageSize, 0),
                            imageSize, CV_16SC2, map1, map2);
    // check if at end
    remap(InitImg, AdjustedImg, map1, map2, cv::INTER_LINEAR);
    return;
}
