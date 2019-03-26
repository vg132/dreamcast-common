#ifndef __CDCCONTROL__H__
#define __CDCCONTROL__H__

#include <kos.h>

struct button_info
{
	unsigned long int nrX;
	unsigned long int nrY;
	unsigned long int nrA;
	unsigned long int nrB;
	unsigned long int nrDown;
	unsigned long int nrUp;
	unsigned long int nrLeft;
	unsigned long int nrRight;
	unsigned long int nrStart;
	unsigned long int nrLeftTrigger;
	unsigned long int nrRightTrigger;
	unsigned long int nrJoyX;
	unsigned long int nrJoyY;
	unsigned long int nrJoy2X;
	unsigned long int nrJoy2Y;
};

class CDCControl
{
private:
	unsigned long int iCurNr;
	button_info bButtonInfo;
	cont_cond_t ccCond, ccLastCond;
	uint8 iMapleAddr;
public:
	void SetMapleAddress(uint8 addr){iMapleAddr=addr;};
	uint8 GetMapleAddress(){return(iMapleAddr);};
	bool Init(unsigned long int nr);
	void Update();
	bool DUp(unsigned long int delay);
	bool DUpDown();
	bool DUpUp();
	bool DDown(unsigned long int delay);
	bool DDownDown();
	bool DDownUp();
	bool DLeft(unsigned long int delay);
	bool DLeftDown();
	bool DLeftUp();
	bool DRight(unsigned long int delay);
	bool DRightDown();
	bool DRightUp();
	bool Start(unsigned long int delay);
	bool StartDown();
	bool StartUp();
	bool A(unsigned long int delay);
	bool ADown();
	bool AUp();
	bool B(unsigned long int delay);
	bool BDown();
	bool BUp();
	bool X(unsigned long int delay);
	bool XDown();
	bool XUp();
	bool Y(unsigned long int delay);
	bool YDown();
	bool YUp();
	bool AnyButtonDown();
	uint8 GetLeftTrigger();
	uint8 GetLeftTrigger(unsigned long int delay);
	bool GetLeftTriggerChange();
	uint8 GetRightTrigger();
	uint8 GetRightTrigger(unsigned long int delay);
	bool GetRightTriggerChange();
	uint8 GetJoy1X();
	uint8 GetJoy1X(unsigned long int delay);
	bool GetJoy1XChange();
	uint8 GetJoy1Y();
	uint8 GetJoy1Y(unsigned long int delay);
	bool GetJoy1YChange();
	uint8 GetJoy2X();
	uint8 GetJoy2X(unsigned long int delay);
	bool GetJoy2XChange();
	uint8 GetJoy2Y();
	uint8 GetJoy2Y(unsigned long int delay);
	bool GetJoy2YChange();
	CDCControl(uint8 addr);
	~CDCControl(void);
};

#endif
