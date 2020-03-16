#pragma once
#include "Params.h"
#include"CLightBlobs.h"



class CArmour
{
  public:
	Rect2f m_ArmourRect;			//装甲板矩形区域
	RotatedRect Rectofnum;          //数字旋转矩形区域
	Rect RectofNum;                 //数字矩形区域
	Mat SolveAngleNumRect;          //将旋转矩形旋转为正常角度返回值为mat
	Point2f m_ArmourCenter;			//装甲板中心坐标(图像坐标系 | pix)
	Point3f m_ArmourPos;			//装甲板中心坐标(摄像头坐标系 | cm)
	Point3f m_ArmourAttitudeAngle;  //装甲板姿态角(世界坐标系 | °)
	bool m_ifSmallArmour;			//T:小装甲 F:大装甲
	RotatedRect m_ArmourLeftLight;  //装甲板左侧灯条
	RotatedRect m_ArmourRightLight; //装甲板右侧灯条
	Point3f m_ArmourLeftPos;		//装甲板左侧灯条中心坐标(cm)
	Point3f m_ArmourRightPos;		//装甲板右侧灯条中心坐标(cm)
	BrightLight m_ArmourLeftBrightLight;
	BrightLight m_ArmourRightBrightLight;

	CArmour();
	CArmour(RotatedRect LeftLight, RotatedRect RightLight);
	CArmour(BrightLight LeftLight, BrightLight RightLight);
	CArmour(LightBlob  LeftLight, LightBlob  RightLight);
	CArmour(Rect rect);
	~CArmour();
	/**
	*Funtion:		Show(Mat displayImg)
	*Description:	在displayImg上画出装甲的位置
	*Calls:			NONE
	*Input:			displayImg: 显示的图像
	*Output:		NONE
	*Return:		NONE
	*Others:		NONE
	*/
	void Show(Mat showImg);
	void changefornumberrect(Mat showImg,CArmour carmour);
	void changefornumberrotatedrect(Mat showImg,CArmour carmour );
	void Enlarge(Point2f tl);
	void solveangleforrotatedrect(Mat showImg,RotatedRect wm,CArmour carmour);
	void solveangleforrotatedrect(Mat showImg, CArmour carmour);
	vector<Point2f> GetPnpPoints();
	vector<Point2f> GetPnpPoints(int);
};


