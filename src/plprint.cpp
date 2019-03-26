#include "dccommon/plprint.hpp"

CPlPrint::CPlPrint()
{
	text=NULL;
	font=NULL;
}

CPlPrint::~CPlPrint()
{
	if(text!=NULL)
		delete text;
	if(font!=NULL)
		delete font;
}

void CPlPrint::SetFont(const char *font_name, int filter)
{
	if(text!=NULL)
		delete text;
	if(font!=NULL)
		delete font;
	text = new fntRenderer();
	font = new fntTexFont(font_name);
	filter_mode=1;
}

void CPlPrint::Print(int x, int y, float r, float g, float b, const char *s, bool fp, int align, int size, float alpha)
{
	float left(0),right(0);
	text->setFilterMode(filter_mode);
	font->setFixedPitch(fp);
	if ((fp) == 1)
	{
		font->setGap(0.1);
		font->setWidth(0.5);
	}
	else
	{
		font->setGap(0.1);
		font->setWidth(1.0);
	}
	text->setFont(font);
	text->setPointSize(size);
	text->begin();
	text->setColor(r, g, b, alpha);
	font->getBBox(s,size,0.0f,&left,&right,NULL,NULL);
	if(align==ALIGN_CENTER)
		text->start2f(x-(int(right)/2), y);
	else if(align==ALIGN_RIGHT)
		text->start2f(x-int(right),y);
	else
		text->start2f(x, y);
	text->puts(s);
	text->end();
}
