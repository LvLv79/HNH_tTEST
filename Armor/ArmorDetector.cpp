#include "Armor.hpp"

ArmorParam armorParam = ArmorParam();

ArmorDetector::ArmorDetector(){
    state = LIGHTS_NOT_FOUND;
}

ArmorDetector::~ArmorDetector(){}

void ArmorDetector::resetDetector()
{
	state = LIGHTS_NOT_FOUND;
	lights.clear();
	armors.clear();
}

/**
* @brief: load and set img
* @param: const Mat& src
*/
void ArmorDetector::setImg(Mat & src){
    vector<Mat> channels;
    src.copyTo(srcImg);
    // 把一个3通道图像转换成3个单通道图像
    split(src,channels);
    Mat grayImg;
    Mat _debugImg;
    //对于图像中红色的物体来说，其rgb分量中r的值最大，g和b在理想情况下应该是0，同理蓝色物体的b分量应该最大,将不想要的颜色减去，剩下的就是我们想要的颜色
    grayImg=channels.at(0)-channels.at(2);//B-R
    int brightness_threshold = 45;//设置阈值，根据相机拍摄实际情况调整
    //阈值化
    threshold(grayImg, binBrightImg, armorParam.bright_threshold, 255, THRESH_BINARY);
	//设置膨胀卷积核
    Mat element = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
    //膨胀
    dilate(binBrightImg, binBrightImg, element);
}

/**
 *@brief: an integrative function to run the Detector
 */
void ArmorDetector::run(Mat & src) {
	//firstly, load and set srcImg  首先，载入并处理图像
	this->setImg(src); //globally srcImg and preprocess it into binBrightImg

	//secondly, reset detector before we findLights or matchArmors
	//随后，重设detector的内容，清空在上一帧中找到的灯条和装甲板
	resetDetector();

	//thirdly, find all the lights in the current frame
	//第三步，在当前图像中找出所有的灯条
	findLights();

    //forthly, if the state is LIGHTS_FOUND (detector found more than two lights) , we match each two lights into an armor
	//第四步，如果状态为LIGHTS_FOUND（找到多于两个灯条），则
	if (state == LIGHTS_FOUND)
	{
		//match each two lights into an armor and if the armor is a suitable one, emplace back it into armors
		//将每两个灯条匹配为一个装甲板，如果匹配出来的装甲板是合适的，则压入armors中
		matchArmors();
		//if the state is ARMOR_FOUND(detector has matched suitable armor), set target armor and last armor
		//如果找到了灯条，则设置好目标装甲板和上一个装甲板
		if (state == ARMOR_FOUND) {
		setTargetArmor();
		}
	}
}

/**
 *@brief: get the vertices and type of target Armor for angle solver 将detector的结果输出
 */
void ArmorDetector::getTargetInfo(vector<Point2f>& armorVertices, Point2f & centerPoint)
{
    armorVertices.clear();
	armorVertices = targetArmor.armorVertices;
    centerPoint = targetArmor.center;
}

/**
 *@brief: return the Detector status 识别程序是否识别到装甲版
 *@return: FOUND(1) NOT_FOUND(0)
 */
bool ArmorDetector::isFoundArmor()
{
    if(state == ARMOR_FOUND)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


///////////////////////////////////////////////////////////  functions  for   debugging      //////////////////////////////////////////////////////////////////


/**
 *@brief: show all the armors matched in a copy of srcImg  在图像中显示找到的所有装甲板
 */
void showArmors(Mat & image, const vector<ArmorBox> & armors, const ArmorBox & targetArmor)
{
	Mat armorDisplay; //Image for the use of displaying armors 展示装甲板的图像
	image.copyTo(armorDisplay); //get a copy of srcImg 源图像的拷贝 
	// if armors is not a empty vector (ARMOR_FOUND) 如果找到了装甲板
	if (!armors.empty())
	{
		putText(armorDisplay, "ARMOR FOUND!", Point(100, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 0), 1, 8, false); //title FOUND 大标题 “找到了装甲板”
		//draw all the armors' vertices and center 画出所有装甲板的顶点边和中心
		for (auto armor : armors)
		{
			//draw the center 画中心
			circle(armorDisplay, armor.center, 2, Scalar(0, 255, 0), 2);
			for (size_t i = 0; i < 4; i++)
			{
				line(armorDisplay, armor.armorVertices[i], armor.armorVertices[(i + 1) % 4], Scalar(255, 255, 0), 2, 8, 0);
			}
			//display its center point x,y value 显示中点坐标
			putText(armorDisplay, to_string(int(armor.center.x)), armor.center, FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);
			putText(armorDisplay, to_string(int(armor.center.y)), armor.center + Point2f(0, 15), FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);

		}
		//connect all the vertices to be the armor contour 画出装甲板轮廓
		for (size_t i = 0; i < 4; i++)
		{
			line(armorDisplay, targetArmor.armorVertices[i], targetArmor.armorVertices[(i + 1) % 4], Scalar(255, 255, 255), 2, 8, 0);
		}
		
	}
	//if armors is a empty vector (ARMOR_NOT FOUND) 如果没找到装甲板
	else
	{
		putText(armorDisplay, "ARMOR NOT FOUND!", Point(100, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 255), 1, 8, false);//title NOT FOUND 大标题 “没找到装甲板”
	}
	//show the result armors image 显示结果图
	imshow("Armor Monitor", armorDisplay);
}



/**
 *@brief: lights, armors, lights to armors every information in one 所有调试用数据输出
 */
void ArmorDetector::showDebugInfo(bool showArmors_ON)
{
	if (showArmors_ON)
		showArmors(srcImg, armors, targetArmor);
}