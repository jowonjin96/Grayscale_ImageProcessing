#pragma once
#include "afxdialogex.h"


// CMulconstantDlg 대화 상자

class CMulconstantDlg : public CDialog
{
	DECLARE_DYNAMIC(CMulconstantDlg)

public:
	CMulconstantDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMulconstantDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MULCONSTANT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_Mulconstant;
};
