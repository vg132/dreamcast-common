#ifndef __CPLPRINT__H__
#define __CPLPRINT__H__

#include <kos.h>
#include <dcplib/fnt.h>

class CPlPrint
{
private:
	fntRenderer *text;
	fntTexFont *font;
	int filter_mode;
public:
	static const int ALIGN_CENTER=40;
	static const int ALIGN_LEFT=41;
	static const int ALIGN_RIGHT=42;

	void SetFont(const char *font_name, int filter=1);
	void Print(int x, int y, float r, float g, float b, const char *s, bool fp=false, int align=ALIGN_LEFT, int size=15, float alpha=1.0f);

	CPlPrint();
	~CPlPrint();
};

#endif
