#pragma once
#include "afxdialogex.h"


// CGammaconstantDlg 대화 상자

class CGammaconstantDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGammaconstantDlg)

public:
	CGammaconstantDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CGammaconstantDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMMACONSTANT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_gammaconstant;
};
