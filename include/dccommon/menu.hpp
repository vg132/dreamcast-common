#ifndef __CMENU__H__
#define __CMENU__H__

#include "plprint.hpp"

class CMenuItem
{
private:
	char* cText;
	bool bEnabled;
	CMenuItem *pNextItem, *pPrevItem;
public:
	void SetEnabled(bool enabled){bEnabled=enabled;};
	bool GetEnabled(){return(bEnabled);};
	void SetText(char* str);
	char* GetText(){return(cText);};
	void SetNext(CMenuItem* item){pNextItem=item;};
	void SetPrev(CMenuItem* item){pPrevItem=item;};
	CMenuItem* GetNext(){return(pNextItem);};
	CMenuItem* GetPrev(){return(pPrevItem);};
	CMenuItem(char* str);
	~CMenuItem();
};

class CMenu
{
private:
	CMenuItem *pFirstItem, *pLastItem, *pCurItem;
	float fSelectedAlpha, fNormalAlpha, fDisableAlpha;
	int iSelectedSize, iNormalSize, iDisableSize, iCurSel, iItems;
	float nRed,nGreen,nBlue, sRed,sGreen,sBlue, dRed,dGreen,dBlue;
	bool bLoop;
public:
	void SetDisableFont(float r, float g, float b, int size, float alpha=1.0f);
	void SetNormalFont(float r, float g, float b, int size, float alpha=1.0f);
	void SetSelectedFont(float r, float g, float b, int size, float alpha=1.0f);
	void AddItem(char* text, bool enable=true);
	void SetLoop(bool loop){bLoop=loop;};
	bool GetLoop(){return(bLoop);};
	bool SelectNext();
	bool SelectPrev();
	bool Select(int pos);
	int GetSelected(){return(iCurSel);};
	CMenuItem* GetMenuItem(int pos);
	void Draw(int x, int y, int yinc, CPlPrint *pPrint);

	CMenu(void);
	~CMenu(void);
};

#endif
