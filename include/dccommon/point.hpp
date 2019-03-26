#ifndef __4432C8C050E068FA1F902A__POINT__HPP__
#define __4432C8C050E068FA1F902A__POINT__HPP__

#include <kos.h>

class CPoint
{
private:
	float m_X;
	float m_Y;
public:
	float GetX(){return(m_X);};
	void SetX(float x){m_X=x;};
	float GetY(){return(m_Y);};
	void SetY(float y){m_Y=y;};
	CPoint(void);
	CPoint(float x, float y);
	~CPoint(void);
};


#endif // __4432C8C050E068FA1F902A__POINT__HPP__
