#include "dccommon/gldraw.hpp"

CGLDraw::CGLDraw(void)
{
}

CGLDraw::~CGLDraw(void)
{
}

// Load a VQ texture
int CGLDraw::LoadVqTxr(const char *fn, int img_size, GLuint *txr, uint32 mask, bool scrambled)
{
	int size;
	pvr_ptr_t txraddr;
	void *data=NULL;

	size=fs_load(fn,&data);
	if(size==-1)
	{
		dbglog(DBG_ERROR, "LoadVqTxr: can't open file '%s'\n", fn);
		return(-1);
	}
	txraddr=pvr_mem_malloc(size);
	if(txraddr==NULL)
	{
		dbglog(DBG_ERROR, "LoadVqTxr: Unable to alocate pvr memory for '%s' (%d)\n", fn,size);
		return(-1);
	}
	memcpy2(txraddr,data,size);
	glGenTextures(1, txr);
	glBindTexture(GL_TEXTURE_2D, txr[0]);
	if(mask==PNG_MASK_ALPHA)
		glKosTex2D(GL_ARGB1555_TWID|GL_VQ_ENABLE, img_size, img_size,txraddr);
	else if(mask==PNG_FULL_ALPHA)
		glKosTex2D(GL_ARGB4444_TWID|GL_VQ_ENABLE, img_size, img_size,txraddr);
	else
		glKosTex2D(GL_RGB565_TWID|GL_VQ_ENABLE, img_size, img_size, txraddr);
	return(0);
}

void CGLDraw::LoadPngTxrToRAM(char* fn, uint32 mask, kos_img_t *img)
{
	void *tmpData;
	if(png_to_img(fn,mask,img))
	{
		printf("can't load %s\n",fn);
		return;
	}
	tmpData = memalign(32, img->w*img->h*2);
	memcpy(tmpData,img->data,img->w*img->h*2);
	kos_img_free(img,0);
	img->data=tmpData;
}
	
void CGLDraw::LoadTxrToVRAM(void *src, GLuint *txr, int lock, uint32 mask)
{
	pvr_ptr_t txraddr(NULL);
	txraddr=pvr_mem_malloc(512*512*2);
	pvr_txr_load_dma(src,txraddr,512*512*2,lock);
	glGenTextures(1,txr);
	glBindTexture(GL_TEXTURE_2D, *txr);
	if(mask==PNG_MASK_ALPHA)
		glKosTex2D(GL_ARGB1555,512,512,txraddr);
	else if(mask==PNG_FULL_ALPHA)
		glKosTex2D(GL_ARGB4444,512,512,txraddr);	
	else
		glKosTex2D(GL_RGB565,512,512, txraddr);
}

// Load a PNG texture to VRAM
void CGLDraw::LoadPngTxrToVRAM(const char *fn, GLuint *txr, uint32 mask, bool scramble)
{
	kos_img_t img;
	pvr_ptr_t txraddr;
	if(png_to_img(fn,mask,&img))
	{
		printf("can't load %s\n",fn);
		return;
	}
	txraddr=pvr_mem_malloc(img.w * img.h*2);
	pvr_txr_load_kimg(&img,txraddr,0);
	kos_img_free(&img,0);
	glGenTextures(1,txr);
	glBindTexture(GL_TEXTURE_2D, *txr);
	if(mask==PNG_MASK_ALPHA)
		glKosTex2D(GL_ARGB1555_TWID,img.w,img.h,txraddr);
	else if(mask==PNG_FULL_ALPHA)
		glKosTex2D(GL_ARGB4444_TWID,img.w,img.h,txraddr);	
	else
		glKosTex2D(GL_RGB565_TWID, img.w, img.h, txraddr);
}

// Load a PCX texture to VRAM
void CGLDraw::LoadPcxTxrToVRAM(const char *fn, GLuint *txr, bool scramble)
{
	kos_img_t img;
	pvr_ptr_t txraddr;

	if (pcx_to_img(fn, &img) < 0)
	{
		printf("can't load %s\n", fn);
		return;
	}

	txraddr = pvr_mem_malloc(img.w * img.h * 2);
	pvr_txr_load_kimg(&img, txraddr, PVR_TXRLOAD_INVERT_Y);
	kos_img_free(&img, 0);

	glGenTextures(1, txr);
	glBindTexture(GL_TEXTURE_2D, *txr);
	glKosTex2D(GL_RGB565_TWID, img.w, img.h, txraddr);
}

// Save the current OpenGL matrices
void CGLDraw::PushMatrices()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
}

// Get last saved OpenGL matrices
void CGLDraw::PopMatrices()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

// 2D mode
void CGLDraw::SetOrtho()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,640,0,480,-1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// 3D mode
void CGLDraw::SetPerspective()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,640.0f/480.0f,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void CGLDraw::SetScissor()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,320.0f/240.0f,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void CGLDraw::DrawBackground(GLuint texture)
{
	PushMatrices();
	SetOrtho();
	glDisable(GL_KOS_AUTO_UV);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBegin(GL_QUADS);
		//Top-Left
		glTexCoord2f(0.0f, 1.0f);glVertex3f(0.0f, 0.0f,0.0f);
		//Top-Right
		glTexCoord2f(1.0f, 1.0f);glVertex3f(640.0f, 0.0f,0.0f);
		//Bottom-Right
		glTexCoord2f(1.0f, 0.0f);glVertex3f(640.0f, 480.0f,0.0f);
		//Bottom-Left
		glTexCoord2f(0.0f, 0.0f);glVertex3f(0.0f, 480.0f,0.0f);
	glEnd();
	glEnable(GL_KOS_AUTO_UV);
	PopMatrices();
}

void CGLDraw::Rect(float x, float y, float w, float h, float alpha, float z)
{
	glBegin(GL_QUADS);
		glNormal3f( 0.0f,-1.0f, 0.0f);
		//Top Left
		glColor4f(1,0,0,alpha);glVertex3f(x,y+h,z);
		//Top Right
		glColor4f(0,1,0,alpha);glVertex3f(x+w,y+h,z);
		//Bottom Left
		glColor4f(0,0,1,alpha);glVertex3f(x+w,y,z);
		//Bottom Right
		glColor4f(1,1,1,alpha);glVertex3f(x,y,z);
	glEnd();
}

void CGLDraw::TexturedRect(GLuint txr, float x, float y, float w, float h, float z1, float z2)
{
	glBindTexture(GL_TEXTURE_2D, txr);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	Rect(x,y,w,h,z1,z2);
}

void CGLDraw::Box(float x, float y, float w, float h, float z1 = 0.7f, float z2 = 0.0f)
{
	/* Comments based on front view */
	glBegin(GL_QUADS);
		// Bottom Face
		glTexCoord2f(0.0f, 1.0f); glVertex3f(   x,   y, z1);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( x+w,   y, z1);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( x+w, y+h, z1);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(   x, y+h, z1);
		// Front Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f(   x,   y, z2);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(   x, y+h, z2);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( x+w, y+h, z2);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( x+w,   y, z2);
		// North wall
		glTexCoord2f(0.0f, 0.0f); glVertex3f(   x, y+h, z2);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(   x, y+h, z1);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( x+w, y+h, z1);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( x+w, y+h, z2);
		// South wall
		glTexCoord2f(1.0f, 0.0f); glVertex3f(   x,   y, z2);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( x+w,   y, z2);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( x+w,   y, z1);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(   x,   y, z1);
		// Right wall
		glTexCoord2f(1.0f, 0.0f); glVertex3f( x+w,   y, z2);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( x+w, y+h, z2);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( x+w, y+h, z1);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( x+w,   y, z1);
		// Left Wall
		glTexCoord2f(0.0f, 0.0f); glVertex3f(   x,   y, z2);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(   x,   y, z1);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(   x, y+h, z1);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(   x, y+h, z2);
	glEnd();
}

void CGLDraw::TexturedBox(GLuint txr, float x, float y, float w, float h, float z1 = 0.7f, float z2 = 0.0f)
{
	glDisable(GL_KOS_AUTO_UV);
	glBindTexture(GL_TEXTURE_2D,txr);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	Box(x,y,w,h,z1,z2);
	glEnable(GL_KOS_AUTO_UV);
}
