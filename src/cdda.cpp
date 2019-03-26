#include "dccommon/cdda.hpp"

CCdda::CCdda(void)
{
	iRvol=250;
	iLvol=250;
	bPlay=false;
}

CCdda::~CCdda(void)
{

}

bool CCdda::IsPlaying()
{
	int status(0), disc_type(0);
	cdrom_reinit();
	cdrom_get_status(&status, &disc_type);
	if(status==CD_STATUS_PLAYING)
		return(true);
	else
		return(false);
}

