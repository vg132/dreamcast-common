#include "dccommon/dccontrol.hpp"

CDCControl::CDCControl(uint8 addr)
{
	iMapleAddr=addr;

	// Rest values
	bButtonInfo.nrX=0;
	bButtonInfo.nrY=0;
	bButtonInfo.nrA=0;
	bButtonInfo.nrB=0;
	bButtonInfo.nrDown=0;
	bButtonInfo.nrUp=0;
	bButtonInfo.nrLeft=0;
	bButtonInfo.nrRight=0;
	bButtonInfo.nrStart=0;
	bButtonInfo.nrLeftTrigger=0;
	bButtonInfo.nrRightTrigger=0;
	bButtonInfo.nrJoyX=0;
	bButtonInfo.nrJoyY=0;
	bButtonInfo.nrJoy2X=0;
	bButtonInfo.nrJoy2Y=0;
}

CDCControl::~CDCControl(void)
{
}

bool CDCControl::Init(unsigned long int nr)
{
	ccLastCond=ccCond;
	if(cont_get_cond(iMapleAddr, &ccCond))
		return(false);
	iCurNr=nr;
	return(true);
}

void CDCControl::Update()
{
}

bool CDCControl::DUp(unsigned long int delay)
{
	if((!(ccCond.buttons & CONT_DPAD_UP))&&((bButtonInfo.nrUp+delay)<iCurNr))
	{
		bButtonInfo.nrUp=iCurNr;
		return(true);
	}
	else if(ccCond.buttons & CONT_DPAD_UP)
	{
		bButtonInfo.nrUp=0;
		return(false);
	}
	return(false);
}

bool CDCControl::DDown(unsigned long int delay)
{
	if((!(ccCond.buttons & CONT_DPAD_DOWN))&&((bButtonInfo.nrDown+delay)<iCurNr))
	{
		bButtonInfo.nrDown=iCurNr;
		return(true);
	}
	else if(ccCond.buttons & CONT_DPAD_DOWN)
	{
		bButtonInfo.nrDown=0;
		return(false);
	}
	return(false);
}

bool CDCControl::DLeft(unsigned long int delay)
{
	if((!(ccCond.buttons & CONT_DPAD_LEFT))&&((bButtonInfo.nrLeft+delay)<iCurNr))
	{
		bButtonInfo.nrLeft=iCurNr;
		return(true);
	}
	else if(ccCond.buttons & CONT_DPAD_LEFT)
	{
		bButtonInfo.nrLeft=0;
		return(false);
	}
	return(false);
}

bool CDCControl::DRight(unsigned long int delay)
{
	if((!(ccCond.buttons & CONT_DPAD_RIGHT))&&((bButtonInfo.nrRight+delay)<iCurNr))
	{
		bButtonInfo.nrRight=iCurNr;
		return(true);
	}
	else if(ccCond.buttons & CONT_DPAD_RIGHT)
	{
		bButtonInfo.nrRight=0;
		return(false);
	}
	return(false);
}

bool CDCControl::Start(unsigned long int delay)
{
	if((!(ccCond.buttons & CONT_START))&&((bButtonInfo.nrStart+delay)<iCurNr))
	{
		bButtonInfo.nrStart=iCurNr;
		return(true);
	}
	else if(ccCond.buttons & CONT_START)
	{
		bButtonInfo.nrStart=0;
		return(false);
	}
	return(false);
}

bool CDCControl::A(unsigned long int delay)
{
	if((!(ccCond.buttons & CONT_A))&&((bButtonInfo.nrA+delay)<iCurNr))
	{
		bButtonInfo.nrA=iCurNr;
		return(true);
	}
	else if(ccCond.buttons & CONT_A)
	{
		bButtonInfo.nrA=0;
		return(false);
	}
	return(false);
}

bool CDCControl::B(unsigned long int delay)
{
	if((!(ccCond.buttons & CONT_B))&&((bButtonInfo.nrB+delay)<iCurNr))
	{
		bButtonInfo.nrB=iCurNr;
		return(true);
	}
	else if(ccCond.buttons & CONT_B)
	{
		bButtonInfo.nrB=0;
		return(false);
	}
	return(false);
}

bool CDCControl::X(unsigned long int delay)
{
	if((!(ccCond.buttons & CONT_X))&&((bButtonInfo.nrX+delay)<iCurNr))
	{
		bButtonInfo.nrX=iCurNr;
		return(true);
	}
	else if(ccCond.buttons & CONT_X)
	{
		bButtonInfo.nrX=0;
		return(false);
	}
	return(false);
}

bool CDCControl::Y(unsigned long int delay)
{
	if((!(ccCond.buttons & CONT_Y))&&((bButtonInfo.nrY+delay)<iCurNr))
	{
		bButtonInfo.nrY=iCurNr;
		return(true);
	}
	else if(ccCond.buttons & CONT_Y)
	{
		bButtonInfo.nrY=0;
		return(false);
	}
	return(false);
}

bool CDCControl::DUpDown()
{
	if((!(ccCond.buttons & CONT_DPAD_UP))&&(ccLastCond.buttons & CONT_DPAD_UP))
		return(true);
	return(false);
}

bool CDCControl::DUpUp()
{
	if((!(ccLastCond.buttons & CONT_DPAD_UP))&&(ccCond.buttons & CONT_DPAD_UP))
		return(true);
	return(false);
}

bool CDCControl::DDownDown()
{
	if((!(ccCond.buttons & CONT_DPAD_DOWN))&&(ccLastCond.buttons & CONT_DPAD_DOWN))
		return(true);
	return(false);
}

bool CDCControl::DDownUp()
{
	if((!(ccLastCond.buttons & CONT_DPAD_DOWN))&&(ccCond.buttons & CONT_DPAD_DOWN))
		return(true);
	return(false);
}

bool CDCControl::DLeftDown()
{
	if((!(ccCond.buttons & CONT_DPAD_LEFT))&&(ccLastCond.buttons & CONT_DPAD_LEFT))
		return(true);
	return(false);
}

bool CDCControl::DLeftUp()
{
	if((!(ccLastCond.buttons & CONT_DPAD_LEFT))&&(ccCond.buttons & CONT_DPAD_LEFT))
		return(true);
	return(false);
}

bool CDCControl::DRightDown()
{
	if((!(ccCond.buttons & CONT_DPAD_RIGHT))&&(ccLastCond.buttons & CONT_DPAD_RIGHT))
		return(true);
	return(false);
}
bool CDCControl::DRightUp()
{
	if((!(ccLastCond.buttons & CONT_DPAD_RIGHT))&&(ccCond.buttons & CONT_DPAD_RIGHT))
		return(true);
	return(false);
}

bool CDCControl::StartDown()
{
	if((!(ccCond.buttons & CONT_START))&&(ccLastCond.buttons & CONT_START))
		return(true);
	return(false);
}

bool CDCControl::StartUp()
{
	if((!(ccLastCond.buttons & CONT_START))&&(ccCond.buttons & CONT_START))
		return(true);
	return(false);
}

bool CDCControl::ADown()
{
	if((!(ccCond.buttons & CONT_A))&&(ccLastCond.buttons & CONT_A))
		return(true);
	return(false);
}

bool CDCControl::AUp()
{
	if((!(ccLastCond.buttons & CONT_A))&&(ccCond.buttons & CONT_A))
		return(true);
	return(false);
}

bool CDCControl::BDown()
{
	if((!(ccCond.buttons & CONT_B))&&(ccLastCond.buttons & CONT_B))
		return(true);
	return(false);
}

bool CDCControl::BUp()
{
	if((!(ccLastCond.buttons & CONT_B))&&(ccCond.buttons & CONT_B))
		return(true);
	return(false);
}

bool CDCControl::XDown()
{
	if((!(ccCond.buttons & CONT_X))&&(ccLastCond.buttons & CONT_X))
		return(true);
	return(false);
}

bool CDCControl::XUp()
{
	if((!(ccLastCond.buttons & CONT_X))&&(ccCond.buttons & CONT_X))
		return(true);
	return(false);
}

bool CDCControl::YDown()
{
	if((!(ccCond.buttons & CONT_Y))&&(ccLastCond.buttons & CONT_Y))
		return(true);
	return(false);
}

bool CDCControl::YUp()
{
	if((!(ccLastCond.buttons & CONT_Y))&&(ccCond.buttons & CONT_Y))
		return(true);
	return(false);
}

uint8 CDCControl::GetLeftTrigger()
{
	return(ccCond.ltrig);
}

uint8 CDCControl::GetLeftTrigger(unsigned long int delay)
{
	if((bButtonInfo.nrLeftTrigger+delay)<iCurNr)
	{
		bButtonInfo.nrLeftTrigger=iCurNr;
		return(ccCond.ltrig);
	}
	else
	{
		bButtonInfo.nrLeftTrigger=0;
		return(0);
	}
}

bool CDCControl::GetLeftTriggerChange()
{
	if(ccCond.ltrig==ccLastCond.ltrig)
		return(false);
	return(true);
}

uint8 CDCControl::GetRightTrigger()
{
	return(ccCond.rtrig);
}

uint8 CDCControl::GetRightTrigger(unsigned long int delay)
{
	if((bButtonInfo.nrRightTrigger+delay)<iCurNr)
	{
		bButtonInfo.nrRightTrigger=iCurNr;
		return(ccCond.rtrig);
	}
	else
	{
		bButtonInfo.nrRightTrigger=0;
		return(0);
	}
}

bool CDCControl::GetRightTriggerChange()
{
	if(ccCond.rtrig==ccLastCond.rtrig)
		return(false);
	return(true);
}

uint8 CDCControl::GetJoy1X()
{
	return(ccCond.joyx);
}

uint8 CDCControl::GetJoy1X(unsigned long int delay)
{
	return(ccCond.joyx);
}

bool CDCControl::GetJoy1XChange()
{
	if(ccCond.joyx==ccLastCond.joyx)
		return(false);
	return(true);
}

uint8 CDCControl::GetJoy1Y()
{
	return(ccCond.joyy);
}

uint8 CDCControl::GetJoy1Y(unsigned long int delay)
{
	return(ccCond.joyy);
}

bool CDCControl::GetJoy1YChange()
{
	if(ccCond.joyy==ccLastCond.joyy)
		return(false);
	return(true);
}

uint8 CDCControl::GetJoy2X()
{
	return(ccCond.joy2x);
}

uint8 CDCControl::GetJoy2X(unsigned long int delay)
{
	return(ccCond.joy2x);
}

bool CDCControl::GetJoy2XChange()
{
	if(ccCond.joy2x==ccLastCond.joy2x)
		return(false);
	return(true);
}

uint8 CDCControl::GetJoy2Y()
{
	return(ccCond.joy2y);
}

uint8 CDCControl::GetJoy2Y(unsigned long int delay)
{
	return(ccCond.joy2y);
}

bool CDCControl::GetJoy2YChange()
{
	if(ccCond.joy2y==ccLastCond.joy2y)
		return(false);
	return(true);
}

bool CDCControl::AnyButtonDown()
{
	if(YDown()||XDown()||ADown()||BDown()||StartDown())
		return(true);
	return(false);
}
