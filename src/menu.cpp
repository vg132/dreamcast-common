#include "dccommon/menu.hpp"

// --------- CMenuItem --------- //

CMenuItem::CMenuItem(char *str)
{
	pNextItem=NULL;
	pPrevItem=NULL;
	cText=new char[strlen(str)];
	strcpy(cText,str);
}

CMenuItem::~CMenuItem()
{
	if(pNextItem!=NULL)
		delete pNextItem;
}

void CMenuItem::SetText(char* str)
{
	if(cText!=NULL)
		delete[] cText;
	cText=new char[strlen(str)];
	strcpy(cText,str);
}

// --------- CMenu --------- //

CMenu::CMenu(void)
{
	pFirstItem=NULL;
	pLastItem=NULL;
	pCurItem=NULL;
	iItems=0;
	iCurSel=0;
}

CMenu::~CMenu(void)
{
	if(pFirstItem!=NULL)
		delete pFirstItem;
}

void CMenu::SetDisableFont(float r, float g, float b, int size, float alpha)
{
	dRed=r;
	dGreen=g;
	dBlue=b;
	iDisableSize=size;
	fDisableAlpha=alpha;
}

void CMenu::SetNormalFont(float r, float g, float b, int size, float alpha)
{
	nRed=r;
	nGreen=g;
	nBlue=b;
	iNormalSize=size;
	fNormalAlpha=alpha;
}

void CMenu::SetSelectedFont(float r, float g, float b, int size, float alpha)
{
	sRed=r;
	sGreen=g;
	sBlue=b;
	iSelectedSize=size;
	fSelectedAlpha=alpha;
}

void CMenu::AddItem(char* text, bool enable)
{
	pCurItem=new CMenuItem(text);
	pCurItem->SetEnabled(enable);
	pCurItem->SetPrev(pLastItem);
	pCurItem->SetNext(NULL);
	if(pFirstItem==NULL)
		pFirstItem=pCurItem;
	if(pLastItem!=NULL)
		pLastItem->SetNext(pCurItem);
	pLastItem=pCurItem;
	iItems++;
}

bool CMenu::SelectNext()
{
	iCurSel++;
	bLoop=true;
	if((iCurSel>=iItems)&&(bLoop==true))
	{
		iCurSel=0;
	}
	else if((iCurSel>=iItems)&&(!bLoop==false))
	{
		iCurSel--;
		return(false);
	}
	return(true);
}

bool CMenu::SelectPrev()
{
	iCurSel--;
	if((iCurSel<0)&&(bLoop))
	{
		iCurSel=iItems-1;
	}
	else if((iCurSel<0)&&(!bLoop))
	{
		iCurSel++;
		return(false);
	}
	return(true);
}

bool CMenu::Select(int pos)
{
	if((pos<0)&&(pos>=iItems))
		return(false);
	iCurSel=pos;
	return(true);
}

CMenuItem* CMenu::GetMenuItem(int pos)
{
	if((pos>=iItems)||(pos<0))
		return(NULL);
	pCurItem=pFirstItem;
	for(int i=0;i<pos;i++)
		pCurItem=pCurItem->GetNext();
	return(pCurItem);
}

void CMenu::Draw(int x, int y, int yinc, CPlPrint *pPrint)
{
	pCurItem=pFirstItem;
	for(int i=0;i<iItems;i++)
	{
		if((i!=iCurSel)&&(pCurItem->GetEnabled()==true))
			pPrint->Print(x,y,nRed,nGreen,nBlue,pCurItem->GetText(),false,pPrint->ALIGN_CENTER,iNormalSize,fNormalAlpha);
		else if(pCurItem->GetEnabled()==false)
			pPrint->Print(x,y,dRed,dGreen,dBlue,pCurItem->GetText(),false,pPrint->ALIGN_CENTER,iDisableSize,fDisableAlpha);
		else if(i==iCurSel)
			pPrint->Print(x,y,sRed,sGreen,sBlue,pCurItem->GetText(),false,pPrint->ALIGN_CENTER,iSelectedSize,fSelectedAlpha);
		y+=yinc;
		pCurItem=pCurItem->GetNext();
	}
}
