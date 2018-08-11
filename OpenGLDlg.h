
// OpenGLDlg.h : header file
//

#pragma once

#include "GlView.h"


// COpenGLDlg dialog
class COpenGLDlg : public CDialogEx
{
// Construction
public:
	COpenGLDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_OPENGL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CGlView* ptrView;
public:
	afx_msg void OnDeltaposSpinMoveX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinRotatex(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinRotatex2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonSevivon();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinRotatey(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinMoveZ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinMoveY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinRotatez(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin4(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnBnClickedButtonsevivon();
	afx_msg void OnBnClickedButtonsevivon2();
	afx_msg void OnFileSave();
	afx_msg void OnFileLoad();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCheck2();
	
	
	
	afx_msg void OnStnClickedPicture();
	
	
	afx_msg void OnDeltaposSpinRotatex3(NMHDR *pNMHDR, LRESULT *pResult);
};
