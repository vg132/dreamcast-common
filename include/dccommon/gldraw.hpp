#ifndef __486CC670EA5DA213628EA__GLDRAW__HPP__
#define __486CC670EA5DA213628EA__GLDRAW__HPP__

#include <kos.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <pcx/pcx.h>
#include <png/png.h>

class CGLDraw
{
public:
	void LoadPngTxrToRAM(char* fn, uint32 mask, kos_img_t *img);
	void LoadTxrToVRAM(void *src, GLuint *txr, int lock=1, uint32 mask=PNG_NO_ALPHA);
	int LoadVqTxr(const char *fn, int img_size, GLuint *txr, uint32 mask=PNG_NO_ALPHA, bool scrambled=false);
	void LoadPcxTxrToVRAM(const char *fn, GLuint *txr, bool scramble=false);
	void LoadPngTxrToVRAM(const char *fn, GLuint *txr, uint32 mask=PNG_NO_ALPHA, bool scramble=false);
	void DrawBackground(GLuint texture);
	void Rect(float x, float y, float w, float h, float alpha=0.7f, float z=0.0f);
	void TexturedRect(GLuint txr, float x, float y, float w, float h, float alpha=0.7f, float z=0.0f);
	void Box(float x, float y, float w, float h, float z1=0.7f, float z2=0.0f);
	void TexturedBox(GLuint txr, float x, float y, float w, float h, float z1=0.7f, float z2=0.0f);
	void PushMatrices();
	void PopMatrices();
	void SetOrtho();
	void SetPerspective();
	void SetScissor();

	CGLDraw(void);
	~CGLDraw(void);
};

#endif // __486CC670EA5DA213628EA__GLDRAW__HPP__
