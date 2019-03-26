#ifndef __ACDC8DCEF3B4D5DFDC77B__TIMER__HPP__
#define __ACDC8DCEF3B4D5DFDC77B__TIMER__HPP__

#include <kos.h>
#include <time.h>

class CTimer
{
private:
	uint64 m_StartTime;
	uint64 m_StopTime;
	uint64 m_PauseTime;

	bool m_Running;
	bool m_Paused;
public:
	void Reset();
	void Start();
	void Stop();
	void Pause();
	bool IsRunning(){return(m_Running);};
	bool IsPaused(){return(m_Paused);};
	uint64 GetTime();
	char* GetTimeString();
	char* GetTimeStringMs();
	CTimer(void);
	~CTimer(void);
};

#endif // __ACDC8DCEF3B4D5DFDC77B__TIMER__HPP__
