#include "dccommon/rect.hpp"

CRect::CRect(void)
: m_X(0),m_Y(0),m_Width(0),m_Height(0)
{
}

CRect::CRect(float x, float y, float width, float height)
: m_X(x), m_Y(y), m_Width(width), m_Height(height)
{

}

CRect::~CRect(void)
{
}

bool CRect::Intersects(CRect *rect)
{
	if(PointInRect(new CPoint(rect->GetX(),rect->GetY())))
		return(true);
	else if(PointInRect(new CPoint(rect->GetX()+rect->GetWidth(),rect->GetY())))
		return(true);
	else if(PointInRect(new CPoint(rect->GetX(),rect->GetY()+rect->GetHeight())))
		return(true);
	else if(PointInRect(new CPoint(rect->GetX()+rect->GetWidth(),rect->GetY()+rect->GetHeight())))
		return(true);
	return(false);
}

bool CRect::PointInRect(CPoint *point)
{
	if((point->GetX()>=m_X)&&(point->GetX()<=(m_X+m_Width))&&
			(point->GetY()>=m_Y)&&(point->GetY()<=(m_Y+m_Height)))
	{
		return(true);
	}
	return(false);
}
