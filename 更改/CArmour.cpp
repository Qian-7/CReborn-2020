#include "CArmour.h"

CArmour::CArmour() {}

CArmour::CArmour(RotatedRect LeftLight, RotatedRect RightLight)
{
	m_ArmourLeftLight = LeftLight;
	m_ArmourRightLight = RightLight;
	m_ArmourCenter = (LeftLight.center + RightLight.center) / 2.0f;
	m_ArmourRect = LeftLight.boundingRect() | RightLight.boundingRect();
}

CArmour::CArmour(BrightLight LeftLight, BrightLight RightLight)
{
	m_ArmourLeftLight = LeftLight.minarearect;
	m_ArmourRightLight = RightLight.minarearect;
	m_ArmourLeftBrightLight = LeftLight;
	m_ArmourRightBrightLight = RightLight;
	m_ArmourCenter = (LeftLight.center + RightLight.center) / 2.0f;
	m_ArmourRect = LeftLight.minarearect.boundingRect() | RightLight.minarearect.boundingRect();
}
CArmour::CArmour(LightBlob LeftLight, LightBlob RightLight)
{
	m_ArmourLeftLight = LeftLight.rect;
	m_ArmourRightLight = RightLight.rect;
	m_ArmourCenter = (LeftLight.rect.center + RightLight.rect.center) / 2.0f;
	m_ArmourRect = LeftLight.rect.boundingRect() | RightLight.rect.boundingRect();

}

CArmour::CArmour(Rect rect)
{
	m_ArmourRect = rect;
	m_ArmourCenter = ((Point2f)rect.tl() + (Point2f)rect.br()) / 2.0f;
}

CArmour::~CArmour() {}

void CArmour::Show(Mat displayImg)
{
	line(displayImg, Point(0, m_ArmourCenter.y), Point(displayImg.cols, m_ArmourCenter.y), Scalar(0, 255, 0), 2);
	line(displayImg, Point(m_ArmourCenter.x, 0), Point(m_ArmourCenter.x, displayImg.rows), Scalar(0, 255, 0), 2);
	rectangle(displayImg,m_ArmourRect, Scalar(0, 255, 0), 2);
	circle(displayImg, m_ArmourCenter, 6, Scalar(0, 0, 255), -1);
}

void CArmour::Enlarge(Point2f tl)
{
	m_ArmourLeftLight.center = m_ArmourLeftLight.center + tl;
	m_ArmourRightLight.center = m_ArmourRightLight.center + tl;
	m_ArmourCenter = m_ArmourCenter + tl;
	m_ArmourRect.tl() = m_ArmourRect.tl() + tl;
	m_ArmourRect.br() = m_ArmourRect.br() + tl;
}

void CArmour::changefornumberrect(Mat showImg, CArmour carmour)
{
	if (carmour.m_ifSmallArmour) {
		RectofNum.height = m_ArmourRect.height + 30;
		RectofNum.width = m_ArmourRect.width - 20;
		RectofNum.x = m_ArmourCenter.x - RectofNum.width / 2;
		RectofNum.y = m_ArmourCenter.y - RectofNum.height / 2;
		rectangle(showImg, RectofNum, Scalar(0, 0, 255), 2);
	}
	else
	{
		RectofNum.height = m_ArmourRect.height + 30;
		RectofNum.width = m_ArmourRect.width - 50;
		RectofNum.x = m_ArmourCenter.x - RectofNum.width / 2;
		RectofNum.y = m_ArmourCenter.y - RectofNum.height / 2;
		rectangle(showImg, RectofNum, Scalar(0, 0, 255), 2);

	}
}
void CArmour::changefornumberrotatedrect(Mat showImg, CArmour carmour)
{

	Rectofnum.center = (carmour.m_ArmourLeftLight.center + carmour.m_ArmourRightLight.center) / 2.0f;
	Rectofnum.angle = (m_ArmourLeftLight.angle + m_ArmourRightLight.angle) / 2;
	Rectofnum.size.height = ((m_ArmourLeftLight.size.height + m_ArmourRightLight.size.height) / 2) * 2.2;
	float a = fabs(m_ArmourLeftLight.center.x - m_ArmourRightLight.center.x);
	float b = fabs(m_ArmourLeftLight.center.y - m_ArmourRightLight.center.y);
	float dis = sqrt(pow(a, 2) + pow(b, 2));
	Rectofnum.size.width = (dis / 2)*1.5;
	Point2f vectpoint[4];
    Rectofnum.points(vectpoint);
    for (int i = 0; i < 4; i++)
    {

		line(showImg, vectpoint[i], vectpoint[(i + 1) % 4], Scalar(0, 0, 255), 2);

	}
}

void CArmour::solveangleforrotatedrect(Mat showimg,RotatedRect wm,CArmour carmour)
{
	float angle = 0.0;

    Size si = wm.size;

	if (wm.size.width <= wm.size.height)

	{

		angle = wm.angle + 90;

		int tm = si.width;

		si.width = si.height;

		si.height = tm;

		//swap(si.width, si.height);

	}

	else

	{

		angle = wm.angle;

	}

	Mat rotmat = getRotationMatrix2D(wm.center, angle, 1);

	
	Mat deal_Mat;
	warpAffine(showimg, deal_Mat, rotmat, showimg.size(), INTER_CUBIC);
	

	getRectSubPix(deal_Mat, si, wm.center, carmour.SolveAngleNumRect);

}
void CArmour::solveangleforrotatedrect(Mat showimg, CArmour carmour)
{
	float angle = 0.0;

	Size si = carmour.Rectofnum.size;

	if (carmour.Rectofnum.size.width <= carmour.Rectofnum.size.height)

	{

		angle = carmour.Rectofnum.angle + 90;

		int tm = si.width;

		si.width = si.height;

		si.height = tm;

		//swap(si.width, si.height);

	}

	else

	{

		angle = carmour.Rectofnum.angle;

	}

	Mat rotmat = getRotationMatrix2D(carmour.Rectofnum.center, angle, 1);


	Mat deal_Mat;
	warpAffine(showimg, deal_Mat, rotmat, showimg.size(), INTER_CUBIC);


	getRectSubPix(deal_Mat, si, carmour.Rectofnum.center, carmour.SolveAngleNumRect);


}


vector<Point2f> CArmour::GetPnpPoints()
{
	vector<Point2f> points;
	Point2f dot_left[4], dot_right[4], dot[4];
	m_ArmourLeftLight.points(dot_left);
	m_ArmourRightLight.points(dot_right);
	if (dot_left[0].y < dot_left[1].y)
	{
		dot[0] = (dot_left[1] + dot_left[2]) / 2;
		dot[1] = (dot_left[0] + dot_left[3]) / 2;
	}
	else
	{
		dot[0] = (dot_left[0] + dot_left[3]) / 2;
		dot[1] = (dot_left[1] + dot_left[2]) / 2;
	}

	if (dot_right[2].y < dot_right[3].y)
	{
		dot[2] = (dot_right[1] + dot_right[2]) / 2;
		dot[3] = (dot_right[0] + dot_right[3]) / 2;
	}
	else
	{
		dot[2] = (dot_right[0] + dot_right[3]) / 2;
		dot[3] = (dot_right[1] + dot_right[2]) / 2;
	}
	for (int i = 0; i < 4; i++)
	{
		points.push_back(dot[i]);
	}
	return points;
}

vector<Point2f> CArmour::GetPnpPoints(int a)
{
	vector<Point2f> points;
	Point2f dot_left[4], dot_right[4], dot[4];
	dot[0] = m_ArmourLeftBrightLight.bottom;
	dot[1] = m_ArmourLeftBrightLight.top;
	dot[3] = m_ArmourRightBrightLight.bottom;
	dot[2] = m_ArmourRightBrightLight.top;
cout<<"points:";
	for (int i = 0; i < 4; i++)
	{
cout<<dot[i]<<" ";
		points.push_back((Point2f)dot[i]);
	}
cout<<endl;
	return points;
}





