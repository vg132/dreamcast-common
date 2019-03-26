#ifndef __695EEDD8E5C6F3EE4B8DA__VMU__HPP__
#define __695EEDD8E5C6F3EE4B8DA__VMU__HPP__

#include <kos.h>
#include <bzlib/bzlib.h>

class CVMUFile
{
private:
	CVMUFile *pNext;
	char *pName;
	int iSize;
	time_t tTime;
public:
	CVMUFile* GetNext(){return(pNext);};
	void SetSize(int size){iSize=size;};
	int GetSize(){return(iSize);};
	void SetTime(time_t time){tTime=time;};
	time_t GetTime(){return(tTime);};
	void SetNext(CVMUFile *next){pNext=next;};
	void SetName(char *name);
	char* GetName(){return(pName);};
	CVMUFile();
	~CVMUFile();
};

class CVMUnit
{
private:
	CVMUnit *pNext;
	int iFreeBlocks;
	maple_device_t *dev;
	CVMUFile *pFirst, *pCurrent, *pTmp;
public:
	CVMUFile* GetFirstFile(){return(pFirst);};
	bool ReadFiles();
	CVMUnit* GetNext(){return(pNext);};
	void SetNext(CVMUnit *next){pNext=next;};
	void SetVMU(maple_device_t *d){dev=d;};
	int GetFreeBlocks(){return(iFreeBlocks);};
	void SetFreeBlocks(int free){iFreeBlocks=free;};
	maple_device_t* GetVMU(){return(dev);};
	CVMUnit();
	~CVMUnit();
};

class CVMU
{
private:
	CVMUnit *pFirst, *pCurrent, *pTmp;
	int iVMUItems;
public:
	int GetVMUItems(){return(iVMUItems);};
	CVMUnit* GetFirstVMUnit(){return(pFirst);};
	bool Refresh();
	char* GetVMUName(maple_device_t *dev);
	bool FileExist(maple_device_t *dev, char *filename);
	char* GetVMUPath(maple_device_t *dev, char* filename=NULL);
	int GetFreeBlocks(maple_device_t *dev);
	int BZCompress(uint8 *dest_data, int *dest_size, uint8 *src_data, int src_size);
	int BZDecompress(uint8 *dest_data, int *dest_size, uint8 *src_data, int src_size);
	bool Write(maple_device_t *dev, char *filename, uint8 *pkg_out, int pkg_size);
	bool Read(maple_device_t *dev, char *filename, vmu_pkg_t *pkg);
	uint8* LoadIcon(const char *path, uint16 *pal);
	CVMU(void);
	~CVMU(void);
};

#endif // __695EEDD8E5C6F3EE4B8DA__VMU__HPP__
