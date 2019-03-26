#include "dccommon/dreamcast.hpp"

CDreamcast::CDreamcast(void)
{
	iNrOfControls=-1;
	maple[0]=0;
	maple[1]=0;
	maple[2]=0;
	maple[3]=0;
}

CDreamcast::~CDreamcast(void)
{
}

uint8 CDreamcast::GetControl(int id)
{
	if(iNrOfControls==-1)
		GetNrOfControls();
	return(maple[id]);
}

uint8 CDreamcast::GetFirstControl()
{
	if(iNrOfControls==-1)
		GetNrOfControls();
	return(maple[0]);
}

int CDreamcast::GetNrOfControls(bool forceRecount)
{
	if((iNrOfControls==-1)||(forceRecount==true))
	{
		iNrOfControls=0;
		for(int i=0;i<4;i++)
		{
			if(cont_get_cond(maple_create_addr(i,0),&cond)==0)
			{
				maple[iNrOfControls]=maple_create_addr(i,0);
				iNrOfControls++;
			}
		}
	}
	return(iNrOfControls);
}
