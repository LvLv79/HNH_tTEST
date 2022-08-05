#pragma once
#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
#include<ros/ros.h>

//#include"../../libCamera/Camera.hpp"
//#include"../../libSolver/Predict/kPredict.hpp"

#define UNIT_PIXEL_W 0.000375
#define UNIT_PIXEL_H 0.000375
using namespace cv;
using namespace std;

class AngleSolver
{
public:
	AngleSolver();
	~AngleSolver();



	/**
	* @brief solve the angles using P4P or PinHole according to the distance
	*/
	Point3d solveAngles(vector<Point3f> POINTS_3D,vector<Point2f> POINTS_2D,Point2f center);



	// calculated by solvePnP
	//s[R|t]=s'  s->world coordinate;s`->camera coordinate
	Mat rVec;    //rot rotation between camera and target center
	Mat tVec;  //trans tanslation between camera and target center

	//Results
	double distance;
	Point3d PNP;


private:
    double GUN_CAM_DISTANCE_Y=-6;
	
    
};
