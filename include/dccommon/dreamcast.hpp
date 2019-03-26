#ifndef __25B4FD9DCA7792CE752F6__DREAMCAST__HPP__
#define __25B4FD9DCA7792CE752F6__DREAMCAST__HPP__

#include <kos.h>

class CDreamcast
{
private:
	cont_cond_t cond;
	uint8 maple[4];
	int iNrOfControls;
public:
	uint8 GetControl(int id);
	uint8 GetFirstControl();
	int GetNrOfControls(bool forceRecount=false);
	CDreamcast(void);
	~CDreamcast(void);
};

#endif // __25B4FD9DCA7792CE752F6__DREAMCAST__H__
