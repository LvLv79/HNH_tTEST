#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
#include "AngleSolver.hpp"
#include "../Camera/Camera.hpp"
//#include"../../libVision/ArmorDetect/ArmorDetect.hpp"
//#include"../../libVision/FuwenDetect/FuwenDetect.hpp"

AngleSolver::AngleSolver()
{
    

}

AngleSolver::~AngleSolver()
{
}
//返回坐标点
Point3d AngleSolver::solveAngles(vector<Point3f> POINTS_3D,vector<Point2f> POINTS_2D,Point2f center)
{
	Cam p1;
	p1.Cam_Init();
	Mat _rvec;
	if(POINTS_2D.empty())
	{
		cout<<"NO POINTS FOUND"<<endl;
	}
	else
	{
		solvePnP(POINTS_3D, POINTS_2D, p1.cameraMatrix, p1.distCoeffs, _rvec, tVec, false, SOLVEPNP_ITERATIVE);

		GUN_CAM_DISTANCE_Y = 0;
		tVec.at<double>(1, 0) -= GUN_CAM_DISTANCE_Y;
		double x_pos = tVec.at<double>(0, 0);
		double y_pos = tVec.at<double>(1, 0);
		double z_pos = tVec.at<double>(2, 0);
		distance = sqrt(x_pos * x_pos + y_pos * y_pos + z_pos * z_pos);
		//cout<<"bbbbbbb"<<distance<<endl;
		//cout<<tVec<<endl;
		PNP.x = x_pos;
		PNP.y = y_pos;
		PNP.z = z_pos;
		
		cout<<"PNP"<<PNP<<endl;
        return PNP;
	}
	
}

