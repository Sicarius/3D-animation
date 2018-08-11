// GlView.h: interface for the CGlView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLVIEW_H__6EDA23AE_B764_11D5_8D52_0004AC3DB799__INCLUDED_)
#define AFX_GLVIEW_H__6EDA23AE_B764_11D5_8D52_0004AC3DB799__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <gl\glaux.h>
#define SIZE 3

class CGlView
{
public:
	CGlView(CWnd *pclWnd);
	~CGlView();

	void generateTextureFromImageFile();

	void vDrawGLScene();

protected:
private:
	void vInitGl(int iWidth, int iHeigth);
	BOOL bSetWindowPixelFormat(HDC hDC);
	BOOL bCreateViewGLContext(HDC hDC);

	// members //////////////////////////////////////////////////////////
public:
protected:
private:
	HGLRC	m_hGLContext;	// required GLContext
	CWnd *m_pclWnd;			// window inwhich opengl will be drawn
	HDC		m_hDC;			// handle to m_pclWnds device context
private:
	float moveX, moveY, moveZ;
	float rotateX, rotateY, rotateZ;
public:
	float getMoveX();
	float getMoveY();
	float getMoveZ();
	void setMoveX(float);
	void setMoveY(float);
	void setMoveZ(float);

	float getRotateX();
	float getRotateY();
	float getRotateZ();
	void setRotateX(float);
	void setRotateY(float);
	void setRotateZ(float);

private:
	GLuint idTexture[SIZE];//IDs for textures
	AUX_RGBImageRec* texture;//struct which contains the width, height and colors of the picture
	float rotY;
private:
	float rotateHatX;
public:
	float getRotateHatX();
	void  setRotateHatX(float);
	void drawSevivon();
private:
	bool isSevivon;
public:
	bool getSevivonStatus();
	void setSevivonStatus(bool);
private:
	float rotateSevivonY;
public:
	float getSevivonY();
	void setSevivonY(float);
};

#endif

