#include "dccommon/vmu.hpp"

//----------CVMUFile----------

CVMUFile::CVMUFile()
{
	pNext=NULL;
	pName=NULL;
}

CVMUFile::~CVMUFile()
{
	if(pNext!=NULL)
		delete pNext;
	if(pName!=NULL)
		delete pName;
}

void CVMUFile::SetName(char *name)
{
	if(pName!=NULL)
		delete pName;
	pName=new char[strlen(name)];
	strcpy(pName,name);
}

//----------CVMUnit----------

CVMUnit::CVMUnit()
{
	dev=NULL;
	pNext=NULL;
	pFirst=NULL;
	pCurrent=NULL;
	pTmp=NULL;
}

CVMUnit::~CVMUnit()
{
	if(pNext!=NULL)
		delete pNext;
	if(pFirst!=NULL)
		delete pFirst;
}

bool CVMUnit::ReadFiles()
{
	file_t d;
	dirent_t *de;
	char *path=new char[15];
	sprintf(path,"/vmu/%c%d",(97+dev->port),dev->unit);
	d=fs_open(path,O_RDONLY|O_DIR);
	delete path;

	if(pFirst!=NULL)
		delete pFirst;
	pFirst=NULL;
	if(!d)
	{
		return(false);
	}
	else
	{
		while((de = fs_readdir(d)))
		{
			pTmp=new CVMUFile();
			pTmp->SetName(de->name);
			pTmp->SetSize(de->size);
			pTmp->SetTime(de->time);
			if(pFirst==NULL)
				pFirst=pTmp;
			else
				pCurrent->SetNext(pTmp);
			pCurrent=pTmp;
		};
	}
	fs_close(d);
	return(true);
}

//----------CVMU----------

CVMU::CVMU(void)
{
	pFirst=NULL;
	pCurrent=NULL;
	pTmp=NULL;
	iVMUItems=0;
}

CVMU::~CVMU(void)
{
	if(pFirst!=NULL)
		delete pFirst;
}

bool CVMU::Refresh()
{
	int i(0);
	maple_device_t *dev=NULL;
	iVMUItems=0;
	if(pFirst!=NULL)
		delete pFirst;
	pFirst=NULL;
	while((dev=maple_enum_type(i++,MAPLE_FUNC_MEMCARD))!=NULL)
	{
		pTmp=new CVMUnit();
		pTmp->SetVMU(dev);
		pTmp->SetFreeBlocks(GetFreeBlocks(dev));
		pTmp->SetNext(NULL);
		if(pFirst!=NULL)
			pCurrent->SetNext(pTmp);
		else
			pFirst=pTmp;
		pCurrent=pTmp;
	}
	return(true);
}

bool CVMU::FileExist(maple_device_t *dev, char *filename)
{
	char* path;
	path=GetVMUPath(dev,filename);
	file_t f = fs_open(path, O_RDONLY);
	delete path;
	if (!f)
		return(false);
	fs_close(f);
	return(true);
}

char* CVMU::GetVMUName(maple_device_t *dev)
{
	char* buffer=new char[3];
	sprintf(buffer,"%c%d",(97+dev->port),dev->unit);
	return(buffer);
}

char* CVMU::GetVMUPath(maple_device_t *dev, char* filename)
{
	char *buffer=new char[50];
	if(filename!=NULL)
		sprintf(buffer,"/vmu/%c%d/%s",(97+dev->port),dev->unit,filename);
	else
		sprintf(buffer,"/vmu/%c%d",(97+dev->port),dev->unit);
	return(buffer);
}

int CVMU::GetFreeBlocks(maple_device_t *dev)
{
	uint16 buf16[256];
	int free_blocks(0),i(0);

	if(vmu_block_read(dev,255,(uint8*)buf16)!=MAPLE_EOK)
		return(-1);
	if(vmu_block_read(dev,buf16[0x46/2],(uint8*)buf16)!=MAPLE_EOK)
		return(-1);
  for(i=0;i<200;++i) 
    if(buf16[i]==0xfffc)
      free_blocks++;
	return(free_blocks);
}

int CVMU::BZCompress(uint8 *dest_data, int *dest_size, uint8 *src_data, int src_size)
{
	return(BZ2_bzBuffToBuffCompress((char*)dest_data,(unsigned int*)dest_size,(char*)src_data,src_size,1,0,0));
}

int CVMU::BZDecompress(uint8 *dest_data, int *dest_size, uint8 *src_data, int src_size)
{
	return(BZ2_bzBuffToBuffDecompress((char*)dest_data,(unsigned int*)dest_size,(char*)src_data,src_size,0,0));
}

bool CVMU::Write(maple_device_t *dev, char *filename, uint8 *pkg_out, int pkg_size)
{
	file_t f;
	char *file=GetVMUPath(dev,filename);
	fs_unlink(file);
	f = fs_open(file, O_WRONLY);
	delete file;
	if (!f)
		return(false);
	fs_write(f, pkg_out, pkg_size);
	fs_close(f);
	return(true);
}

bool CVMU::Read(maple_device_t *dev, char *filename, vmu_pkg_t *pkg)
{
	char* path;
	int size;
	file_t f;
	path=GetVMUPath(dev,filename);
	f = fs_open(path, O_RDONLY);
	delete path;
	if (!f)
		return(false);
	size=fs_total(f);
	if(!size)
		return(false);
	uint8 buffer[size];
	fs_read(f,&buffer,size);
	fs_close(f);
	if(vmu_pkg_parse((uint8*)&buffer,pkg)!=0)
		return(false);
	return(true);
}

// Load a palettized bmp.
// Returns a icon from a bmp image
uint8* CVMU::LoadIcon(const char *path, uint16 *pal)
{
	file_t f;
	unsigned short bpp;
	int ncolors; 
	unsigned short magic;
	unsigned int height, width, clr_used,i;
	unsigned char r, g, b;
	int size, rsize;
	uint8 *buf;

	f = fs_open(path, O_RDONLY);
	if (!f) return NULL;
	fs_read(f, &magic, 2);
	if (magic != 19778)
	{
		fs_close(f);
		printf("%s: not a BMP file (%u)\n", path, (unsigned int)magic);
		return NULL;
	}
	fs_seek(f, 16, SEEK_CUR);
	fs_read(f, &width, 4);
	fs_read(f, &height, 4);
	fs_seek(f, 2, SEEK_CUR);
	fs_read(f, &bpp, 2);
	ncolors = 1 << bpp;
	fs_seek(f, 16, SEEK_CUR);
	fs_read(f, &clr_used, 4);
	fs_seek(f, 4, SEEK_CUR);

	for (i = 0; i < clr_used; i++)
	{
		fs_read(f, &b, 1);
		fs_read(f, &g, 1);
		fs_read(f, &r, 1);
		fs_seek(f, 1, SEEK_CUR);
		r >>= 4; g >>= 4; b >>= 4;
		*pal = (0xf << 12) | (r << 8) | (g << 4) | b;
		pal++;
	}

	size = height * width * bpp / 8;
	buf = (uint8*)malloc(size);
	rsize = fs_read(f, buf, size);
	fs_close(f);
	return buf;
}
