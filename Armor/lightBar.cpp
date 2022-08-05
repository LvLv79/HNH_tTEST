#include "Armor.hpp"


LightBar::LightBar(){
	lightRect = RotatedRect();
	length = 0;
	width = 0;
	height = 0;
	center = Point2f();
	angle = 0;
}

LightBar::LightBar(const RotatedRect &lightRect){
	this->lightRect = lightRect;
	length = MAX(lightRect.size.height, lightRect.size.width);
	width = lightRect.size.width;
	height = lightRect.size.height; 
	center = lightRect.center;
	if (lightRect.angle > 90)
		angle = lightRect.angle - 180;
	else
		angle = lightRect.angle;
}

LightBar::~LightBar(){}