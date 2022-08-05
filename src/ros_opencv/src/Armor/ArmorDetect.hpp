#pragma once
#include<opencv2/opencv.hpp>
#include<ros/ros.h>
#include<sensor_msgs/Image.h>
#include<cv_bridge/cv_bridge.h>
class ArmorDetect{
    public:
    ArmorDetect(ros::NodeHandle& nh);
    ~ArmorDetect();
    /**
    *@brief:find boundRect and centerPoint
    *pram:
    *@return description of the return value
    */
    void findArmorPoint(cv::Mat img,bool appearRect = false);

    /**
    * @brief Set armor size
    * @param type: input target type small/big
    * @param width: the width of armor (mm)
    * @param height: the height of armor (mm)
    */
    //cv::Point2i calRectcenter(cv::Rect rt);

    cv::Point2f ArmorCenter;
    std::vector<cv::Point2f> armorImagePoints;
    //Object points in world coordinate
	std::vector<cv::Point3f> ARMOR_POINTS_3D;
        
    private:
    int areaFilter = 200; 
        
    };
    ros::Publisher img_pub_;   
    enum
    {
        BLUE,
        GREEN,
        ARMOR_RED,
        ENERGY_RED,
        ARMOR_BLUE,
        ENERGY_BLUE,
    };
