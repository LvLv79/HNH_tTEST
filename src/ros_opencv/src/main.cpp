#include<iostream>
using namespace std;
#include"Armor/ArmorDetect.hpp"
#include"Pose/AngleSolver.hpp"
#include"Camera/Camera.hpp"
#include<opencv2/opencv.hpp>
#include<visualization_msgs/Marker.h>
#include<geometry_msgs/PoseStamped.h>
int main(int argc, char **argv)
{
    ros::init(argc, argv, "ros_opencv");
    ros::NodeHandle n;
    //创建发布者，发布RVIZ图形
    ros::Publisher point_pub_ = n.advertise<visualization_msgs::Marker>("pnp_data",1);
    while (1)
    {
        //if(button)break;
        Cam pp;
        cv::Mat pre_Frame;
        ArmorDetect dd(n);
        AngleSolver AS;
        bool detect_flag = false;
        pp.getImage();
        dd.findArmorPoint(pp.InitImg,1);
        Point3d pnp = AS.solveAngles(dd.ARMOR_POINTS_3D,dd.armorImagePoints,dd.ArmorCenter);
        //Point3d newPNP(KF.getPredict(AS.PNP.x,1),KF.getPredict(AS.PNP.y,2),KF.getPredict(AS.PNP.z,3));
        //cout<<"KF:"<<KF.getPredict(AS.PNP.x,1)<<KF.getPredict(AS.PNP.y,2)<<KF.getPredict(AS.PNP.z,3)<<endl;
        //std::cout<<"AS.newPNP:"<<AS.newPNP[0]<<endl;
        //AS.getAngle(AS.PNP);
            
        //circle(curr_Frame, center, 10, Scalar(255, 255, 0), 4);
        //serial code is expected to be updated


        //putText(oriimg,std::to_string(x_speed),Point(center.x+50,center.y+50),cv::FONT_HERSHEY_PLAIN,2,(255,0,0),2);
        //dd.ArmorCenter.clear();
        //pre_Frame = curr_Frame;
        //创建长方体
        visualization_msgs::Marker marker;
        marker.scale.x = 0.1;
        marker.scale.y = 0.5;
        marker.scale.z = 0.3;
        marker.color.r = 0.0f;
        marker.color.g = 1.0f;
        marker.color.b = 0.0f;
        marker.color.a = 1.0;
        marker.header.frame_id = "cam_link";
        marker.header.stamp = ros::Time::now();
        marker.ns = "pnp_box";
        marker.type = visualization_msgs::Marker::CUBE;
        marker.action = visualization_msgs::Marker::MODIFY;
        marker.pose.position.x = -pnp.z/1000;
        marker.pose.position.y = pnp.x/1000;
        marker.pose.position.z = pnp.y/1000;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 1.0;
        //发布图形话题
        point_pub_.publish(marker);
        cv::waitKey(100);
        }






    return 0;
}
