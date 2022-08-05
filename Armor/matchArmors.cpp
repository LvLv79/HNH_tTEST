#include"Armor.hpp"

void eraseRepeatArmor(vector<ArmorBox> & armors);
bool armorScore(const ArmorBox & a_armor, const ArmorBox & b_armor, const ArmorBox & lastArmor);

/**
* @brief: match lights into armors
*/
void ArmorDetector::matchArmors(){
	for (int i = 0; i < lights.size() - 1; i++)
	{
		for (int j = i + 1; j < lights.size(); j++)
		{
			ArmorBox armor = ArmorBox(lights[i], lights[j]); //two lights match into an armor
			if (armor.isSuitableArmor()) //filter 
			{
				armor.l_index = i; //set index of left light
				armor.r_index = j; //set index of right light
				armors.emplace_back(armor); //push into armors
			}
		}
		eraseRepeatArmor(armors);//delete the error armor caused by single lightbar
	}
	if (armors.empty()) {
		state = ARMOR_NOT_FOUND;
		return; 
	} 
	else {
		state = ARMOR_FOUND;
		return;
	}
}

/**
 *@brief: set the privious targetArmor as lastArmor and then choose the most valuable armor from current armors as targetArmor
 *			将上一帧的目标装甲板作为lastArmor选择本帧图像中所有装甲板里面价值最大的装甲板作为目标装甲板
 */
void ArmorDetector::setTargetArmor()
{
	if (state == ARMOR_NOT_FOUND)  targetArmor = ArmorBox(); //not found armr then set a default armor as lastArmor 如果状态为没有找到装甲板，则将lastArmor设置为默认的ArmorBox
	else if (state == ARMOR_FOUND) {
		ArmorBox mva = armors[0]; //mva most valuable armor
		for (int i = 1; i < armors.size(); i++) //find the most valuable
		{
			if (armorScores(armors[i], mva, lastArmor)) mva = armors[i];
		}
		targetArmor = mva; //set the mva as the targetArmor of this frame
	}
	lastArmor = targetArmor; //first set the targetArmor(of last frame) as lastArmor 将上一帧的targetArmor设置为本帧的lastArmor
}


/**
 *@brief: delete wrong armor caused by single lightBar
 */
void eraseRepeatArmor(vector<ArmorBox> & armors)
{
   
	while(true)
	{
	int length = armors.size();
	vector<ArmorBox>::iterator it = armors.begin();

	for (size_t i = 0; i < length; i++)
		for (size_t j = i + 1; j < length; j++)
		{
			if (armors[i].l_index == armors[j].l_index ||
				armors[i].l_index == armors[j].r_index ||
				armors[i].r_index == armors[j].l_index ||
				armors[i].r_index == armors[j].r_index)
			{
				if(armors[i].getDeviationAngle() > armors[j].getDeviationAngle())
				{
					armors.erase(it + i);
				}
				else
				{
					armors.erase(it + j);
				}
				
			}
			break;
		}
		break;
	}
	//armors.erase(std::remove_if(armors.begin(), armors.end(), [](ArmorBox a) {return a.type == W_ARMOR;}),armors.end());
}


/**
 *@brief: get the distance of two points(a and b) 获取两点之间的距离 
 */
float getPointsDistance(const Point2f& a, const Point2f& b) {
	float delta_x = a.x - b.x;
	float delta_y = a.y - b.y;
	return sqrt(delta_x * delta_x + delta_y * delta_y);
}


/**
 *@brief: compare a_armor to b_armor according to their distance to lastArmor(if exit, not a default armor) and their area and armorNum
 *		  比较a_armor装甲板与b_armor装甲板的打击度，判断a_armor是否比b_armor更适合打击（通过装甲板数字是否与目标装甲板数字匹配，装甲板与lastArmor的距离以及装甲板的面积大小判断）
 */
bool armorScores(const ArmorBox & a_armor, const ArmorBox & b_armor, const ArmorBox & lastArmor)
{
	float a_score = 0;  // shooting value of a_armor a_armor的打击度
	float b_score = 0;  //shooting value of b_armor b_armor的打击度
	a_score += a_armor.armorRect.area(); //area value of a a_armor面积得分
	b_score += b_armor.armorRect.area(); //area value of b b_armor面积得分
	
	if (lastArmor.armorVertices.empty()!=0) {  //if lastArmor.armorRect is not a default armor means there is a true targetArmor in the last frame 上一帧图像中存在目标装甲板
		float a_distance = getPointsDistance(a_armor.center, lastArmor.center); //distance score to the lastArmor(if exist) 装甲板距离得分，算负分
		float b_distance = getPointsDistance(b_armor.center, lastArmor.center); //distance score to the lastArmor(if exist) 装甲板距离得分，算负分
		a_score -= a_distance * 2;
		b_score -= b_distance * 2;
	}
	cout<<"a-score:"<<a_score<<endl;
	return a_score > b_score; //judge whether a is more valuable according their score 根据打击度判断a是否比b更适合打击
}
