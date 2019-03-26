#include "dccommon/timer.hpp"

CTimer::CTimer(void)
:m_StartTime(0), m_StopTime(0), m_PauseTime(0), m_Running(false), m_Paused(false)
{
}

CTimer::~CTimer(void)
{
}

void CTimer::Pause()
{
	if(m_Running)
	{
		if(!m_Paused)
		{
			m_PauseTime=timer_ms_gettime64();
		}
		else
		{
			uint64 tmp=timer_ms_gettime64()-m_PauseTime;
			m_StartTime+=tmp;
			m_PauseTime=0;
		}
		m_Paused=!m_Paused;
	}
}

uint64 CTimer::GetTime()
{
	if(m_Running)
	{
		if(m_Paused)
			return(m_PauseTime-m_StartTime);
		else
			return(timer_ms_gettime64()-m_StartTime);
	}
	else
	{
		return(m_StopTime-m_StartTime);
	}
}

char* CTimer::GetTimeString()
{
	char *buffer=new char[6];
	struct tm tm;
	time_t t=GetTime()/1000;
  localtime_r(&t, &tm);
  sprintf(buffer, "%02d:%02d", tm.tm_min, tm.tm_sec);
	return(buffer);
}

char* CTimer::GetTimeStringMs()
{
	char *buffer=new char[6];
	struct tm tm;
	uint16 ms=GetTime()-((GetTime()/1000)*1000);
	time_t t=GetTime()/1000;
  localtime_r(&t, &tm);
  sprintf(buffer, "%02d:%03d", tm.tm_sec,ms);
	return(buffer);
}

void CTimer::Reset()
{
	m_Running=false;
	m_Paused=false;
	m_PauseTime=0;
	m_StartTime=0;
	m_StopTime=0;
}

void CTimer::Start()
{
	Reset();
	m_Running=true;
	m_StartTime=timer_ms_gettime64();
}

void CTimer::Stop()
{
	m_Running=false;
	m_Paused=false;
	m_StopTime=timer_ms_gettime64();
}
