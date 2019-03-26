#include "dccommon/id3.hpp"

const char *id3_genres[148] =
{
	"Blues", "Classic Rock", "Country", "Dance", "Disco", "Funk", "Grunge", "Hip-Hop",
	"Jazz", "Metal", "New Age", "Oldies", "Other", "Pop", "R&B", "Rap", "Reggae",
	"Rock", "Techno", "Industrial", "Alternative", "Ska", "Death Metal", "Pranks", "Soundtrack",
	"Euro-Techno", "Ambient", "Trip-Hop", "Vocal", "Jazz+Funk", "Fusion", "Trance", "Classical",
	"Instrumental", "Acid", "House", "Game", "Sound Clip", "Gospel", "Noise", "Alt",
	"Bass", "Soul", "Punk", "Space", "Meditative", "Instrumental Pop",
	"Instrumental Rock", "Ethnic", "Gothic", "Darkwave", "Techno-Industrial", "Electronic",
	"Pop-Folk", "Eurodance", "Dream", "Southern Rock", "Comedy", "Cult",
	"Gangsta Rap", "Top 40", "Christian Rap", "Pop/Funk", "Jungle", "Native American",
	"Cabaret", "New Wave", "Psychedelic", "Rave", "Showtunes", "Trailer", "Lo-Fi", "Tribal",
	"Acid Punk", "Acid Jazz", "Polka", "Retro", "Musical", "Rock & Roll", "Hard Rock", "Folk",
	"Folk/Rock", "National Folk", "Swing", "Fast-Fusion", "Bebob", "Latin", "Revival",
	"Celtic", "Bluegrass", "Avantgarde", "Gothic Rock", "Progressive Rock",
	"Psychedelic Rock", "Symphonic Rock", "Slow Rock", "Big Band", "Chorus", "Easy Listening",
	"Acoustic", "Humour", "Speech", "Chanson", "Opera", "Chamber Music", "Sonata", "Symphony",
	"Booty Bass", "Primus", "Porn Groove", "Satire", "Slow Jam", "Club", "Tango",
	"Samba", "Folklore", "Ballad", "Power Ballad", "Rhythmic Soul", "Freestyle", "Duet",
	"Punk Rock", "Drum Solo", "A Cappella", "Euro-House", "Dance Hall", "Goa",
	"Drum & Bass", "Club-House", "Hardcore", "Terror", "Indie", "BritPop", "Negerpunk",
	"Polsk Punk", "Beat", "Christian Gangsta Rap", "Heavy Metal", "Black Metal", "Crossover",
	"Contemporary Christian", "Christian Rock", "Merengue", "Salsa", "Thrash Metal",
	"Anime", "JPop", "Synthpop"
};


CID3::CID3()
{
	myID3.ready=0;
	myID3.album=NULL;
	myID3.band=NULL;
	myID3.comment=NULL;
	myID3.genre=NULL;
	myID3.title=NULL;
	myID3.year=NULL;
	myID3.ID3TAG=NULL;
	myID3.NEWID3=NULL;
}

CID3::~CID3()
{
	if(myID3.album!=NULL)
		delete[] myID3.album;
	if(myID3.band!=NULL)
		delete[] myID3.band;
	if(myID3.comment!=NULL)
		delete[] myID3.comment;
	if(myID3.genre!=NULL)
		delete[] myID3.genre;
	if(myID3.title!=NULL)
		delete[] myID3.title;
	if(myID3.year!=NULL)
		delete[] myID3.year;
	if(myID3.ID3TAG!=NULL)
		delete[] myID3.ID3TAG;
	if(myID3.NEWID3!=NULL)
		delete[] myID3.NEWID3;
}

//////////////////////////////////////////////////////////
//AutoDetect() - function that automatically detects	//
//		ID3 version.									//
//////////////////////////////////////////////////////////

int CID3::AutoDetect(FILE* fin)
{
	char fBuffer[3];
	bool found1(false), found2(false);
	int rValue;

	fseek(fin,0,SEEK_SET);
	fread((char*)fBuffer,sizeof(char),3,fin);

	if(strstr(fBuffer, "ID3"))
		found2 = true;

	fseek(fin,-128,SEEK_END);
	fread((char*)fBuffer,sizeof(char),3,fin);

	if(strstr(fBuffer, "TAG"))
		found1 = true;

	rValue = ((found1 == true) && (found2 == true)) ? CID3::ID3_FOUNDBOTH : (found1 == true) ? CID3::ID3_FOUND1 : (found2 == true) ? CID3::ID3_FOUND2 : 0;
	myID3.version = ((found1 == true) && (found2 == true)) ? CID3::ID3_VERSION2 : (found1 == true) ? CID3::ID3_VERSION1 : (found2 == true) ? CID3::ID3_VERSION2 : 0;

	return(myID3.version);
}

int CID3::AutoDetect(char *filepath)
{
	FILE *fin;
	fin=fopen(filepath,"r");
	AutoDetect(fin);
	fclose(fin);

	return(myID3.version);
}

//////////////////////////////////////////////////////////
//ConsolidateSpaces() - Remove large gaps in your fields//
//////////////////////////////////////////////////////////

int CID3::ConsolidateSpaces(char *wkString)
{
	char *tmpStr;
	int whitespaces = 0, currstrpos = 0;

	tmpStr	= new char[strlen(wkString)+1];

	tmpStr[0] = '\0';

	for(uint32 z=0;z<strlen(wkString);z++)
	{
		if(wkString[z] != 32)
		{
			if(whitespaces > 0) { tmpStr[currstrpos] = 32; currstrpos++; }
			tmpStr[currstrpos] = wkString[z];
			tmpStr[z+1] = '\0';
			currstrpos++;
			whitespaces = 0;
		}
		else
			whitespaces++;
	}
	strcpy(wkString, tmpStr);
	return(0);
}

int CID3::EncryptSync(char *sBuffer, int num, int start, int numsyncs)
{
	for(int z = 0;z < numsyncs; z++)
		sBuffer[start+numsyncs-z-1] = ExtractBits(num, ((z*7)+1), 7);
	return(0);
}

//////////////////////////////////////////////////////////
//Clear() - Must be called to clear all previous id3	//
//		id3 data.  Should be used after an id3 has been	//
//		created and the user would like to create a new //
//		id3.											//
//////////////////////////////////////////////////////////

int CID3::Clear()
{
	myID3.dynbuffer		= 0;
	myID3.currsize		= 0;
	myID3.currpos		= 0;
	myID3.size			= 0;
	myID3.version		= 0;
	myID3.flags			= 0;
	if(myID3.album!=NULL)
		delete[] myID3.album;
	if(myID3.band!=NULL)
		delete[] myID3.band;
	if(myID3.comment!=NULL)
		delete[] myID3.comment;
	if(myID3.genre!=NULL)
		delete[] myID3.genre;
	if(myID3.title!=NULL)
		delete[] myID3.title;
	if(myID3.year!=NULL)
		delete[] myID3.year;
	if(myID3.ID3TAG!=NULL)
		delete[] myID3.ID3TAG;
	if(myID3.NEWID3!=NULL)
		delete[] myID3.NEWID3;

	myID3.album=NULL;
	myID3.band=NULL;
	myID3.comment=NULL;
	myID3.genre=NULL;
	myID3.title=NULL;
	myID3.year=NULL;
	myID3.ID3TAG=NULL;
	myID3.NEWID3=NULL;

	myID3.ready = 0;
	return(0);
}

bool CID3::FrameIsNull(char *frame, int chars)
{
	bool IsNull(true);

	for(int x = 0; x < chars; x++)
		if(frame[x] != 0)
			IsNull = false;
	return(IsNull);
}

const char *CID3::GetAlbum()
{
	return(myID3.album);
}

const char *CID3::GetArtist()
{
	return(myID3.band);
}

const char *CID3::GetComments()
{
	return(myID3.comment);
}

const char *CID3::GetGenre()
{
	if(myID3.version==CID3::ID3_VERSION1)
    return(id3_genres[myID3.genre[0]]);
	else
		return(myID3.genre);
}

char CID3::GetGenreValue()
{
	return(myID3.genre[0]);
}

int CID3::GetSize()
{
	return(myID3.size);
}

const char *CID3::GetTrackNum()
{
	return(myID3.tracknum);
}

const char *CID3::GetTrackTitle()
{
	return(myID3.title);
}

const char *CID3::GetYear()
{
	return(myID3.year);
}

//////////////////////////////////////////////////////////
//Initialize() - Must be called before and id3			//
//		manipulation can occur.  Not called just for	//
//		first id3 tag, but before every new id3 tag		//
//		the user wants to create.  Basically you have to//
//		call flush() when finished with a tag, and then //
//		Initialize() to begin a tag.					//
//////////////////////////////////////////////////////////

int CID3::Initialize()
{
	myID3.header[0]		= '\0';
	myID3.dynbuffer		= 0;
	myID3.currsize		= 10;
	myID3.currpos		= 10;
	myID3.size			= 0;
	myID3.version		= 0;
	myID3.flags			= 0;
	myID3.album			= new char[1];
	myID3.band			= new char[1];
	myID3.comment		= new char[1];
	myID3.genre			= new char[1];
	myID3.title			= new char[1];
	myID3.year			= new char[1];
	myID3.ID3TAG		= new char[1];
	myID3.NEWID3		= new char[1];
	myID3.tracknum		= new char[1];
	myID3.album[0]		= '\0';
	myID3.band[0]		= '\0';
	myID3.comment[0]	= '\0';
	myID3.genre[0]		= '\0';
	myID3.title[0]		= '\0';
	myID3.year[0]		= '\0';
	myID3.ID3TAG[0]		= '\0';
	myID3.NEWID3[0]		= '\0';
	myID3.tracknum[0]	= '\0';

	myID3.ready = 1;

	return(0);
}

int CID3::IsPrimed()
{
	return(myID3.ready);
}

//////////////////////////////////////////////////////////
//LoadID3() - Use this to load id3 data from file.		//
//////////////////////////////////////////////////////////

int CID3::LoadID3(char *filepath)
{
	char	tmpHeader[10];
	FILE *fin;
	fin=fopen(filepath,"r");
	AutoDetect(fin);
	fseek(fin,0,SEEK_SET);
	switch(myID3.version)
	{
		case CID3::ID3_VERSION2:
			fread((char*)&myID3.header,sizeof(char),10,fin);
			if(!strstr(myID3.header, "ID3"))
			{
				fclose(fin);
				return(-1);
			}
			tmpHeader[0] = '\0';
			myID3.size			= GetFourByteSyncSafe(myID3.header[6], myID3.header[7], myID3.header[8], myID3.header[9]);
			myID3.flags			= (myID3.header[6] & 255);
			myID3.footer		= ExtractBits(myID3.flags, 5, 1);
			myID3.extended		= ExtractBits(myID3.flags, 7, 1);
			myID3.experimental	= ExtractBits(myID3.flags, 6, 1);
			myID3.ID3TAG		= new char[myID3.size-(myID3.footer * 10)];

			fseek(fin,0,SEEK_SET);
			fread(myID3.ID3TAG,sizeof(char),myID3.size-(myID3.footer*10),fin);

			StrCopy(tmpHeader, myID3.ID3TAG, 10);

			myID3.album		= RetrField("TALB");
			myID3.band		= RetrField("TPE1");
			myID3.comment	= RetrField("COMM");
			myID3.genre		= RetrField("TCON");
			myID3.title		= RetrField("TIT2");
			myID3.tracknum	= RetrField("TRCK");
			myID3.year		= RetrField("TYER");

			if(myID3.comment[5]>0)
				strcpy(&myID3.comment[0], &myID3.comment[5]);
			break;
		case CID3::ID3_VERSION1:
			myID3.ID3TAG = new char[129];
			myID3.album = new char[31];
			myID3.band = new char[31];
			myID3.comment = new char[31];
			myID3.genre = new char[2];
			myID3.title = new char[31];
			myID3.year = new char[5];

			fseek(fin,-128,SEEK_END);
			fread((char*)&myID3.header,sizeof(char),3,fin);

			if(!strstr(myID3.header, "TAG"))
			{
				myID3.title[0] = '\0';
				myID3.band[0] = '\0';
				myID3.album[0] = '\0';
				myID3.year[0] = '\0';
				myID3.comment[0] = '\0';
				myID3.genre[0] = '\0';
				fclose(fin);
				return(-1);
			}

			fread((char*)myID3.title,sizeof(char),30,fin);
			fread((char*)myID3.band,sizeof(char),30,fin);
			fread((char*)myID3.album,sizeof(char),30,fin);
			fread((char*)myID3.year,sizeof(char),4,fin);
			fread((char*)myID3.comment,sizeof(char),30,fin);
			fread((char*)&myID3.genre[0],sizeof(char),1,fin);
			fseek(fin,-128,SEEK_END);
			fread((char*)myID3.ID3TAG,sizeof(char),128,fin);

			myID3.album[29] = '\0';
			myID3.band[29] = '\0';
			myID3.comment[29] = '\0';
			myID3.genre[1] = '\0';
			myID3.title[29] = '\0';
			myID3.year[4] = '\0';

			break;
		default:
			fclose(fin);
			return(-1);
			break;
	}
	fclose(fin);
	return(0);
}

//////////////////////////////////////////////////////////
//LoadID3() - Retrieve a field from the original id3 tag//
//		that cannot be accessed through built in		//
//		methods.  For instance "TCOP" (copyright data)	//
//		is not something we can retrieve by calling any //
//		of the Get functions.  If we call				//
//		RetrField("TCOP") we can retrieve this field.	//
//////////////////////////////////////////////////////////

char *CID3::RetrField(char *identifier)
{
	if((myID3.version != CID3::ID3_VERSION2) || (IsPrimed() == 0))
		return(0);

	char *dest;
	char tmpHeader[10];
	int framesize = 0, pos = 0;

	tmpHeader[0] = '\0';

	StrCopy(tmpHeader, myID3.ID3TAG, 10);

	while(!FrameIsNull(tmpHeader, 10))
	{
		pos += 10;
		framesize = GetFourByteSyncSafe(tmpHeader[4], tmpHeader[5], tmpHeader[6], tmpHeader[7]);

		if(strstr(tmpHeader, identifier))
		{
			dest = new char[framesize+1];
			dest[framesize] = '\0';
			StrCopy(dest, &myID3.ID3TAG[pos + 1], framesize - 1);
			dest[framesize-1] = '\0';
			return(dest);
		}
		pos += framesize;
		if(pos > myID3.size)
		{
			dest = new char[1];
			dest[0] = '\0';
			return(dest);
		}
		StrCopy(tmpHeader, &myID3.ID3TAG[pos], 10);
	}
	dest = new char[1];
	dest[0] = '\0';
	return(dest);
}

//////////////////////////////////////////////////////////
//SetVersion() - MUST BE CALLED BEFORE ANY ID3			//
//		OPERATIONS CAN TAKE PLACE!!!!!	MUST BE CALLED	//
//		BEFORE EVERY TAG THAT IS CREATED AND OR LOADED  //
//		AND MODIFIED									//
//////////////////////////////////////////////////////////

int CID3::SetVersion(int version)
{
	myID3.version = version;
	return(version);
}

char *CID3::StrCopy(char *pDest, const char *toCopy, int length)
{
	for(int x = 0; x < length; x++)
		pDest[x] = toCopy[x];
	return(pDest);
}

int CID3::StrFill(char *str, int fillx, int ch)
{
	for(int x = 0; x < fillx; x++)
		str[x] = ch;
	return(0);
}
