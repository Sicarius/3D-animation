// GlView.cpp: implementation of the CGlView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GlView.h"

#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library

#pragma comment(lib, "legacy_stdio_definitions.lib")
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGlView::CGlView(CWnd *pclWnd)
	: moveX(0), moveY(0), moveZ(0), rotateX(0), rotateY(4), rotateZ(0)
	, rotateHatX(0)
	, isSevivon(false)
	, rotateSevivonY(0)
{
	m_pclWnd = pclWnd;
	m_hDC  = ::GetDC(pclWnd->m_hWnd);
	BOOL bSuccess;

	RECT rect; 
	m_pclWnd->GetClientRect(&rect);
	int iWidth = rect.right - rect.left;
	int iHeight = rect.bottom - rect.top;

	bSuccess = bSetWindowPixelFormat(m_hDC);
	ASSERT(&bSuccess);

	bSuccess = bCreateViewGLContext(m_hDC);
	ASSERT(&bSuccess);

	vInitGl(iWidth, iHeight);

	generateTextureFromImageFile();
}

// +
// *****************************************************************************
//   Module      :  CGlView::~CGlView()
//   Access      :  Public
//   Input       :  None
//   Output      :  None
//   Return Val  :  None
//   Exceptions  :  None
//   Desc        :  This function is the one and only destructor. It provides
//									clean up and performs any needed shutdown procedures
//
//   Notes       :  None
// *****************************************************************************
// -
CGlView::~CGlView()
{
	// make the rendering context not current
	if(wglGetCurrentContext()!=NULL) 
		wglMakeCurrent(NULL, NULL);
	
	// delete the Context
  if (m_hGLContext!=NULL)
  {
		wglDeleteContext(m_hGLContext);
    m_hGLContext = NULL;
  }

}



void CGlView::drawSevivon()//sevivon
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();
	glTranslatef(0.0f, 1.0f, -8.0f);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	//glRotatef(50, 1, 0, 0);

	glPushMatrix();
		glTranslatef(0.0f, -3.0f, 0.0f);//trick
		glRotatef(rotateSevivonY, 0, 1, 0);
		glRotatef(20, 1, 0, 0);
		glTranslatef(0.0f, 3.0f, 0.0f);//trick

		GLUquadricObj* obj;
		obj = gluNewQuadric();

		//stick
		glPushMatrix();
			glRotatef(-90, 1, 0, 0);
			glColor3f(0.8f, 0.1f, 0.0f);
			gluCylinder(obj, 0.5, 0.5, 2, 32, 32);
		glPopMatrix();
	
		//Cube
		glPushMatrix();
			glRotatef(90, 1, 0, 0);
			glColor3f(0.2f, 0.5f, 1.0f);
			gluCylinder(obj, 2.0, 2.0, 1, 4, 4);

			//disable adding color and light effects
			glDisable(GL_COLOR_MATERIAL);
			glDisable(GL_LIGHT0);
			glDisable(GL_LIGHTING);

			gluDisk(obj, 0.0, 2.0, 4, 4);

			glEnable(GL_COLOR_MATERIAL);
			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		//Pyramid
		glPushMatrix();
			glColor3f(0.9f, 0.8f, 1.5f);
			glTranslatef(0.0f, -1.0f, 0.0f);
			glRotatef(90, 1, 0, 0);
			gluCylinder(obj, 2.0, 0.0, 2, 4, 4);
		glPopMatrix();
	glPopMatrix();

	//disable adding color and light effects
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	//Floor
	glPushMatrix();
		glColor3f(0.5f, 0.8f, 1.0f);
		glTranslatef(0.0f, -3.0f, 0.0f);
		glRotatef(90, 1, 0, 0);
		gluDisk(obj, 1.0, 3.0, 32, 32);
	glPopMatrix();

	gluDeleteQuadric(obj);


	SwapBuffers(m_hDC);
}


// +
// *****************************************************************************
//   Module      :  void CGlView::DrawGLScene()	
//   Access      :  Public
//   Input       :  None
//   Output      :  None
//   Return Val  :  None
//   Exceptions  :  None
//   Desc        :  This function is called contiously to provide realtime OpenGl
//									drawing
//
//   Notes       :  Place all reatime rendering code here
// *****************************************************************************
// -

void CGlView::vDrawGLScene()//dahlil
{

	
	//glClearColor(0,0,0,0);//background color
	
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer

	glLoadIdentity();//ifus matriza yehida
	glTranslatef(0.0f, 0.0f, -8.0f);//hazazaa
	//texture start
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, idTexture[2]);////select texture number: idTexture[0]
	//texture end
	
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-5, -4, 0);

		glTexCoord2f(1,0);
		glVertex3f(-5, 4, 0);

		glTexCoord2f(1,1);
		glVertex3f(5, 4, 0);

		glTexCoord2f(0,1);
		glVertex3f(5, -4, 0);
	glEnd();




	glTranslatef(moveX, moveY, moveZ);
	glRotatef(rotateX, 1, 0, 0);
	glRotatef(rotateY, 0, 1, 0);
	glRotatef(rotateZ, 0, 0, 1);

	////axes
	//glBegin(GL_LINES);//every 2 dots connect line
	////x  RED
	//glColor3f(1.0f, 0.0f, 0.0f);//red color
	//glVertex3f(-3.0f, -1.3f, 0.0f);//left dot of hand
	//glVertex3f(3.0f, -1.3f, 0.0f);//right dot of hand
	////y  GREEN 
	//glColor3f(0.0f, 1.0f, 0.0f);
	//glVertex3f(0.0f, -3.0f, 0.0f);
	//glVertex3f(0.0f, 3.0f, 0.0f);
	////z  BLUE
	//glColor3f(0.0f, 0.0f, 1.0f);
	//glVertex3f(0.0f, 0.0f, -3.0f);
	//glVertex3f(0.0f, 0.0f, 3.0f);
	//glEnd();


	//add effects of color and light
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	//head
	GLUquadricObj* obj;
	obj = gluNewQuadric();//metoda lehakzaa dinamit
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	

	
	glRotatef(-90, 1, 0, 0);
	glColor3f(5,3,1);//color hair

	glPushMatrix();
	glRotatef(0, 1, 0, 0);
	gluCylinder(obj, 2, 0.1, 1.4,2, 2);//change hair style 


	glPopMatrix();
	glRotatef(90, 1, rotateHatX, rotateHatX);
	glColor3f(1,1,1);//head color
	gluSphere(obj, 1.1, 8, 8);//head


	//eyes
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);//kviat zeva obyekt

	//right
	glColor3f(3,2,1);//eyes and nose color

	glTranslatef(0.7f, -0.1f, 0.9f);//hazaza(x,y,z)
	//glScalef(1.0f, 0.8f, 1.0f);//metihat kivuz
	gluSphere(obj, 0.12, 32, 32);//ziyur obyekt
									 
	//left
	glTranslatef(0.7f * -2.0f, 0.1f, 0.0f);//hazaza(x,y,z)

	//glScalef(1.0f, 0.8f, 1.0f);//metihat kivuz
	gluSphere(obj, 0.12, 32, 32);//ziyur obyekt
	
	//glPushMatrix();
	//nose
	
	glScalef(1.0f, 2.0f, 1.0f);//metihat kivuz
	glTranslatef(0.7f * 1.f, -0.05f, 0.0f);//hazaza(x,y,z)
	gluSphere(obj, 0.2, 32, 32);//ziyur obyekt
	

	/*
	glTranslatef(-1 * 0.7 * -2, 0.0f, 0.0f);
	glScalef(1.0f, 0.5f, 1.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glTranslatef(-1 * 0.7f, -1 * -0.2f, -1 * 0.9f);
	*/
	
	glPopMatrix();//body

	glRotatef(90, 1, 0, 0);
	glColor3f(0.6f, 0.392f, 0.f);
	gluCylinder(obj, 0.5, 1.3, 3, 16, 16);//change body shape -1.3 change width body
	glRotatef(-90, 1, 0, 0);



	gluDeleteQuadric(obj);

	 glPushMatrix();//mouth
 glRotatef(35, 1, 0, 0);
 glColor3f(1,0,0);
 gluCylinder(obj, 1, 0.25, 1.15, 7, 7);
 glPopMatrix(); 

 glPopMatrix();//left hand
 glRotatef(80, 120, 70, 0);
 glColor3f(0.f, 0.392f, 0.6f);
 gluCylinder(obj, 0.2, 0.2, 2.2, 3, 3);
 glRotatef(50, 30, -10, -10);


 glPopMatrix();//right hand

 glRotatef(50,8, -80, -50);
 glColor3f(0.f, 0.392f, 0.6f);
 gluCylinder(obj, 0.2, 0.2, 2.2, 3, 3);
 glRotatef(50, 30, -10, -10);
 
 ///leg test

											   

	//disable adding color and light effects
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	

	



	// swap the buffer
	SwapBuffers(m_hDC);


	
}

// +
// *****************************************************************************
//   Module      :  BOOL CGlView::SetWindowPixelFormat(HDC hDC)
//   Access      :  Private
//   Input       :  hDC - Handle to the GL windwos device context
//   Output      :  None
//   Return Val  :  TRUE  - success
//									FALSE - failure
//   Exceptions  :  None
//   Desc        :  This function sets up the required pixelformat descriptor
//
//   Notes       :  None
// *****************************************************************************
// -
BOOL CGlView::bSetWindowPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;

    pixelDesc.nSize     = sizeof(PIXELFORMATDESCRIPTOR);
    pixelDesc.nVersion	= 1;

    pixelDesc.dwFlags   =    
	
		PFD_DRAW_TO_WINDOW |// Format Must Support Window
		PFD_SUPPORT_OPENGL |// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,	// Must Support Double Buffering
		PFD_TYPE_RGBA,		// Request An RGBA Format
		32,					// Select A 16Bit Color Depth
		0, 0, 0, 0, 0, 0,	// Color Bits Ignored (?)
		0,					// No Alpha Buffer
		0,					// Shift Bit Ignored (?)
		0,					// No Accumulation Buffer
		0, 0, 0, 0,			// Accumulation Bits Ignored (?)
		16,					// 16Bit Z-Buffer (Depth Buffer)  
		0,					// No Stencil Buffer
		0,					// No Auxiliary Buffer (?)
		PFD_MAIN_PLANE,		// Main Drawing Layer
		0,					// Reserved (?)
		0, 0, 0;			// Layer Masks Ignored (?)

    int iGLPixelIndex = ChoosePixelFormat( hDC, &pixelDesc);
		ASSERT(&iGLPixelIndex);

    if (SetPixelFormat( hDC, iGLPixelIndex, &pixelDesc))
			return false;

    return TRUE;
}

// +
// *****************************************************************************
//   Module      :  BOOL CGlView::CreateViewGLContext(HDC hDC)
//   Access      :  Private
//   Input       :  hDC - Handle to the GL windwos device context
//   Output      :  None
//   Return Val  :  TRUE  - success
//									FALSE - failure
//   Exceptions  :  None
//   Desc        :  This function sets up the required GLContext
//
//   Notes       :  None
// *****************************************************************************
// -
BOOL CGlView::bCreateViewGLContext(HDC hDC)
{
		m_hGLContext = wglCreateContext(hDC);
    if (m_hGLContext == NULL)
      return FALSE;

    if (wglMakeCurrent(hDC, m_hGLContext)==FALSE)
			return FALSE;

    return TRUE;
}

// +
// *****************************************************************************
//   Module      :  void CGlView::InitGl(int iWidth, int iHeigth)
//   Access      :  Private
//   Input       :  iWidth  - width of the window
//									iHeight - height of the window
//   Output      :  None
//   Return Val  :  None
//   Exceptions  :  None
//   Desc        :  This function initializes all OpenGL rendering specifics
//
//   Notes       :  None
// *****************************************************************************
// -
void CGlView::vInitGl(int iWidth, int iHeigth)
{
	glShadeModel(GL_SMOOTH);								
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);		
	glClearDepth(1.0f);									
	glEnable(GL_DEPTH_TEST);							
	glDepthFunc(GL_LEQUAL);								
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	

	glViewport(0,0,iWidth,iHeigth);						

	glMatrixMode(GL_PROJECTION);						
	glLoadIdentity();								

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)iWidth/(GLfloat)iHeigth,0.45f,100.0f);

	glMatrixMode(GL_MODELVIEW);							
	glLoadIdentity();		
}
void CGlView::generateTextureFromImageFile()
{
	glGenTextures(SIZE, idTexture);
	char* images[SIZE] = { "book.bmp","book.bmp","book.bmp" };
	for (int i = 0; i < SIZE; i++)
	{
		texture = auxDIBImageLoadA(images[i]);
		if (texture)
		{
			glBindTexture(GL_TEXTURE_2D, idTexture[i]);//select texture number: idTexture[i]
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//if target is smaller than source --> use Linear algorithm to minimize it
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//if target is larger than source --> use Linear algorithm to maximize it
			glTexImage2D(GL_TEXTURE_2D, 0, 3, texture->sizeX, texture->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->data);//save the texture in memory

			free(texture);//free texture
		}
		texture = NULL;
	}
}
float CGlView::getMoveX()
{
	return moveX;
}

float CGlView::getMoveY()
{
	return moveY;
}

float CGlView::getMoveZ()
{
	return moveZ;
}

void CGlView::setMoveX(float moveX)
{
	this->moveX = moveX;
}

void CGlView::setMoveY(float moveY)
{
	this->moveY = moveY;
}

void CGlView::setMoveZ(float moveZ)
{
	this->moveZ = moveZ;
}


float CGlView::getRotateX()
{
	return rotateX;
}

float CGlView::getRotateY()
{
	return rotateY;
}

float CGlView::getRotateZ()
{
	return rotateZ;
}

void CGlView::setRotateX(float rotateX)
{
	this->rotateX = rotateX;
}

void CGlView::setRotateY(float rotateY)
{
	this->rotateY = rotateY;
}

void CGlView::setRotateZ(float rotateZ)
{
	this->rotateZ = rotateZ;
}

float CGlView::getRotateHatX()
{
	return rotateHatX;
}

void CGlView::setRotateHatX(float rotateHatX)
{
	this->rotateHatX = rotateHatX;
}

bool CGlView::getSevivonStatus()
{
	return isSevivon;
}

void CGlView::setSevivonStatus(bool sevivon)
{
	this->isSevivon = sevivon;
}
float CGlView::getSevivonY()
{
	return rotateSevivonY;
}

void CGlView::setSevivonY(float rotateSevivonY)
{
	this->rotateSevivonY = rotateSevivonY;
}
