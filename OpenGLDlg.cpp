
// OpenGLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGL.h"
#include "OpenGLDlg.h"
#include "afxdialogex.h"
#include "OpenSaveFile.h"
#include <fstream>
#include <iostream>
#include <thread>
#include <windows.h>

#include<mmsystem.h>
#include<stdlib.h>
using namespace std;
#pragma comment( lib, "winmm" )
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	
// Dialog Data
	enum { IDD = IDD_ABOUTBOX };
	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};


CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// COpenGLDlg dialog



COpenGLDlg::COpenGLDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COpenGLDlg::IDD, pParent)
	, ptrView(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenGLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COpenGLDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MOVE_X, &COpenGLDlg::OnDeltaposSpinMoveX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_RotateX, &COpenGLDlg::OnDeltaposSpinRotatex)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_RotateX2, &COpenGLDlg::OnDeltaposSpinRotatex2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK1, &COpenGLDlg::OnBnClickedCheck1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_ROTATEY, &COpenGLDlg::OnDeltaposSpinRotatey)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MOVE_Z, &COpenGLDlg::OnDeltaposSpinMoveZ)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MOVE_Y, &COpenGLDlg::OnDeltaposSpinMoveY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_ROTATEZ, &COpenGLDlg::OnDeltaposSpinRotatez)
//	ON_BN_CLICKED(IDC_BUTTONSEVIVON, &COpenGLDlg::OnBnClickedButtonsevivon)
	ON_BN_CLICKED(IDC_BUTTONSEVIVON2, &COpenGLDlg::OnBnClickedButtonsevivon2)
	ON_COMMAND(ID_FILE_SAVE32771, &COpenGLDlg::OnFileSave)
	ON_COMMAND(ID_FILE_LOAD, &COpenGLDlg::OnFileLoad)
	ON_BN_CLICKED(IDOK, &COpenGLDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &COpenGLDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK2, &COpenGLDlg::OnBnClickedCheck2)
	
	
	
	
	
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_RotateX3, &COpenGLDlg::OnDeltaposSpinRotatex3)
END_MESSAGE_MAP()


// COpenGLDlg message handlers

BOOL COpenGLDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CWnd* ptrPicture = GetDlgItem(IDC_PICTURE);
	//ptrView = new CGlView(this);
	ptrView = new CGlView(ptrPicture);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COpenGLDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COpenGLDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

		ptrView->vDrawGLScene();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COpenGLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void COpenGLDlg::OnDeltaposSpinMoveX(NMHDR *pNMHDR, LRESULT *pResult)//moves the figure left and right
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	ptrView->setMoveX(ptrView->getMoveX() - 1 * pNMUpDown->iDelta);
	
	ptrView->vDrawGLScene();

	*pResult = 0;
}


void COpenGLDlg::OnDeltaposSpinRotatex(NMHDR *pNMHDR, LRESULT *pResult)//move the figure on x [zir]
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	
	ptrView->setRotateX(ptrView->getRotateX() + 5 * pNMUpDown->iDelta);

	ptrView->vDrawGLScene();

	*pResult = 0;
}

void COpenGLDlg::OnDeltaposSpinRotatex3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	ptrView->setRotateHatX(ptrView->getRotateHatX() + 0.9 * pNMUpDown->iDelta);
	ptrView->vDrawGLScene();

	*pResult = 0;
}


void COpenGLDlg::OnDeltaposSpinRotatex2(NMHDR *pNMHDR, LRESULT *pResult)//kivun hasear
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	ptrView->setRotateHatX(ptrView->getRotateHatX() +0.1 * pNMUpDown->iDelta);

	ptrView->vDrawGLScene();

	*pResult = 0;
}


void COpenGLDlg::OnTimer(UINT_PTR nIDEvent)//dance
{
	
		ptrView->setRotateY(ptrView->getRotateY() - 3);
		ptrView->vDrawGLScene();
	
	
		
		
	CDialogEx::OnTimer(nIDEvent);
}



void COpenGLDlg::OnBnClickedCheck1()//timer
{
	
	static bool checked = true;
	if (checked)
	{
		SetTimer(1, 30, NULL);
		checked = false;
		ptrView->setRotateZ(ptrView->getRotateZ() + 165);
		ptrView->setMoveZ(ptrView->getMoveZ() + 4);

	}
	else
	{
		KillTimer(1);
		checked = true;
		ptrView->setRotateZ(ptrView->getRotateZ() - 15);
		ptrView->setMoveZ(ptrView->getMoveZ() - 2);
		ptrView->vDrawGLScene();
	}
	CButton *m_ctlCheck = (CButton*)GetDlgItem(IDC_CHECK1);
	int ChkBox = m_ctlCheck->GetCheck();
	CString str;

	if (ChkBox == BST_UNCHECKED)
		PlaySound(NULL, 0, 0);

	else if (ChkBox == BST_CHECKED)
		PlaySound(TEXT("a3.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void COpenGLDlg::OnDeltaposSpinRotatey(NMHDR *pNMHDR, LRESULT *pResult)//move the figure on y [zir]
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	
	ptrView->setRotateY(ptrView->getRotateY() - 5 * pNMUpDown->iDelta);

	ptrView->vDrawGLScene();

	*pResult = 0;
}


void COpenGLDlg::OnDeltaposSpinMoveZ(NMHDR *pNMHDR, LRESULT *pResult)//kiruv verihuk hadmut
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	
	ptrView->setMoveZ(ptrView->getMoveZ() - 1 * pNMUpDown->iDelta);

	ptrView->vDrawGLScene();

	*pResult = 0;
}


void COpenGLDlg::OnDeltaposSpinMoveY(NMHDR *pNMHDR, LRESULT *pResult)//hazazat dmut lemala lemata
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	
	ptrView->setMoveY(ptrView->getMoveY() - 1 * pNMUpDown->iDelta);

	ptrView->vDrawGLScene();

	*pResult = 0;
}


void COpenGLDlg::OnDeltaposSpinRotatez(NMHDR *pNMHDR, LRESULT *pResult)//sivuv hadmut al zir z
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	
	ptrView->setRotateZ(ptrView->getRotateZ() + 5 * pNMUpDown->iDelta);

	ptrView->vDrawGLScene();

	*pResult = 0;
}






void COpenGLDlg::OnBnClickedButtonsevivon2()//reset
{
	ptrView->setMoveX(0);
	ptrView->setMoveY(0);
	ptrView->setMoveZ(0);
	ptrView->setRotateX(0);
	ptrView->setRotateY(4);
	ptrView->setRotateZ(0);
	ptrView->setRotateHatX(0);
	ptrView->vDrawGLScene();
}


void COpenGLDlg::OnFileSave()
{
	//MessageBox(L"OnFileSave");

	//CFileDialog fileDialog(false);
	//int res = fileDialog.DoModal();

	//ofstream myFile("file1.txt", ios::app);//append
	//char str[] = "Hi All";
	//myFile.write(str, sizeof(char)*strlen(str));//myFile << str;


	ofstream myFile("file1.txt");
	OpenSaveFile saveFile;
	saveFile.moveX = ptrView->getMoveX();
	saveFile.moveY = ptrView->getMoveY();
	saveFile.moveZ = ptrView->getMoveZ();
	saveFile.rotateX = ptrView->getRotateX();
	saveFile.rotateY = ptrView->getRotateY();
	saveFile.rotateZ = ptrView->getRotateZ();
	myFile.write((char*)&saveFile, sizeof(OpenSaveFile));

	myFile.close();
}


void COpenGLDlg::OnFileLoad()
{
	//CFileDialog fileDialog(true);
	//int res = fileDialog.DoModal();

	ifstream myFile("file1.txt");
	OpenSaveFile openFile;
	myFile.read((char*)&openFile, sizeof(OpenSaveFile));
	myFile.close();

	ptrView->setMoveX(openFile.moveX);
	ptrView->setMoveY(openFile.moveY);
	ptrView->setMoveZ(openFile.moveZ);
	ptrView->setRotateX(openFile.rotateX);
	ptrView->setRotateY(openFile.rotateY);
	ptrView->setRotateZ(openFile.rotateZ);

	ptrView->vDrawGLScene();
}


void COpenGLDlg::OnBnClickedOk()//ok button
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}





void COpenGLDlg::OnBnClickedCancel()//cancel button
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}



void COpenGLDlg::OnBnClickedCheck2()
{
	static bool checked = true;
	if (checked)
	{
		SetTimer(1, 30, NULL);
		checked = false;
		ptrView->setRotateZ(ptrView->getRotateZ() + 15);
		ptrView->setMoveZ(ptrView->getMoveZ() + 2);
	}
	else
	{
		KillTimer(1);
		checked = true;
		ptrView->setRotateZ(ptrView->getRotateZ() - 15);
		ptrView->setMoveZ(ptrView->getMoveZ() - 2);
		ptrView->vDrawGLScene();

	}

}


















