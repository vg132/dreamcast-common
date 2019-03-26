#ifndef __CCDDA__H__
#define __CCDDA__H__

#include <kos.h>

class CCdda
{
private:
	int iEnd, iStart, iLvol, iRvol;
	bool bPlay;
public:
	bool IsPlaying();
	int GetFirstTrackNr(){return(iStart);};
	int GetLastTrackNr(){return(iEnd);};
	void Play();
	void Stop();
	void Pause();
	bool Init();
	void Resume();
	void SetRightVol(int vol);
	int GetLeftVol(){return(iLvol);};
	void SetLeftVol(int vol);
	int GetRightVol(){return(iRvol);};
	void SetTotalVol(int vol);
	int GetTotalVol(){return(iLvol);};
	CCdda(void);
	~CCdda(void);
};

#endif
