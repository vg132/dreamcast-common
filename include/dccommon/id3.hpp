//FileName:	id3.hpp
//Purpose:	Class that allows you to easily manipulate id3 data.  In upcoming versions more field options will be available
//Author:	Brad Zasada
//Homepage:	http://www.bradsoft.net
//Contact:	brad@bradsoft.net
//Report Bugs:  Report bugs via email or post them in the bugs section on my bbs.
//Revision Dates:	2-19-01 (initial writing)
//					2-27-01 (Beta 2)
//2004-04-09 - Converted for use with Dreamcast by Viktor Gars (http://www.vgsoftware.com/)

#ifndef __141412203B91B22179977__ID3__HPP__
#define __141412203B91B22179977__ID3__HPP__

#include <string.h>
#include <stdio.h>

#define ExtractBits(value, start, length) ((value >> (start - 1)) & ((1 << length) - 1))
#define GetFourByteSyncSafe(value1, value2, value3, value4) (((value1 & 255) << 21) | ((value2 & 255) << 14) | ((value3 & 255) << 7) | (value4 & 255))
#define CreateFourByteField(value1, value2, value3, value4) (((value1 & 255) << 24) | ((value2 & 255) << 16) | ((value3 & 255) << 8) | (value4 & 255))

struct ID3Struct
{
	char* band;
	char* album;
	char* title;
	char* comment;
	char* genre;
	char* year;
	char* ID3TAG;
	char* NEWID3;
	char* tracknum;
	char header[10];
	int currsize;
	int currpos;
	int size;
	int version;
	int ready;
	int dynbuffer;
	int	footer, extended, experimental;
	long flags;
};

class CID3
{
private:
	char* RetrField(char* identifier);
	int EncryptSync(char* sBuffer, int num, int start, int numsyncs);	
	char *StrCopy(char* pDest, const char* toCopy, int length);
	int StrFill(char* str, int fillx, int ch);
	int ConsolidateSpaces(char* wkString);
	bool FrameIsNull(char* frame, int chars);
	int IsPrimed();
	int GetSize();
	ID3Struct myID3;
public:
	static const int ID3_VERSION2=19990;
	static const int ID3_VERSION1=12000;
	static const int ID3_FOUND1=13000;
	static const int ID3_FOUND2=14000;
	static const int ID3_FOUNDBOTH=15000;

	const char* GetArtist();
	const char* GetTrackTitle();
	const char* GetTrackNum();
	const char* GetAlbum();
	const char* GetYear();
	const char* GetComments();
	const char* GetGenre();
	char GetGenreValue();
	int LoadID3(char* filepath);
	int Initialize();
	int SetVersion(int version);
	int AutoDetect(FILE* fin);
	int AutoDetect(char* filepath);
	int Clear();

	CID3();
	~CID3();
};

#endif // __141412203B91B22179977__ID3__HPP__
