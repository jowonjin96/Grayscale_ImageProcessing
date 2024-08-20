#pragma once
#include "afxdialogex.h"


// CZoomoutconstantDlg 대화 상자

class CZoomoutconstantDlg : public CDialog
{
	DECLARE_DYNAMIC(CZoomoutconstantDlg)

public:
	CZoomoutconstantDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CZoomoutconstantDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ZOOMOUTCONSTANT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_zoomoutconstant;
};
