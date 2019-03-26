#ifndef __CCC169B6C5AAF0728FE53F__RECT__HPP__
#define __CCC169B6C5AAF0728FE53F__RECT__HPP__

#include <kos.h>
#include "dccommon/point.hpp"

class CRect
{
private:
	float m_X;
	float m_Y;
	float m_Width;
	float m_Height;
public:
	float GetX(){return(m_X);};
	void SetX(float x){m_X=x;};
	float GetY(){return(m_Y);};
	void SetY(float y){m_Y=y;};
	float GetWidth(){return(m_Width);};
	void SetWidth(float width){m_Width=width;};
	float GetHeight(){return(m_Height);};
	void SetHeight(float height){m_Height=height;};

	bool Intersects(CRect *rect);
	bool PointInRect(CPoint *point);

	CRect(void);
	CRect(float x, float y, float width, float height);
	~CRect(void);
};


#endif // __CCC169B6C5AAF0728FE53F__RECT__HPP__
