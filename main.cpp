#include <iostream>
#include <opencv2/opencv.hpp>
#include"Armor/Armor.hpp"
using namespace std;
using namespace cv;
int main()
{
    ArmorDetector ad;
    LightBar lb;
    ArmorBox ab;
    string imgpath = "../1920.png";
    string videopath="../1920_1.avi";
    VideoCapture capture(videopath);
    //Mat img = imread(imgpath,1); 
    Mat frame;
    while (true)
    {
        capture.read(frame);
        imshow("opencv_test", frame);
        waitKey(20);
        ad.run(frame);
        ad.showDebugInfo(1);

        
    }
    /*Mat img = imread(imgpath,1); 
    ad.run(img);
    ad.showDebugInfo(0, 0, 0, 1, 0, 0, 1);
    waitKey(0);*/
    return 0;
}