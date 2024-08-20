// GammaconstantDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GrayScaleImageProcessingRC1.h"
#include "afxdialogex.h"
#include "GammaconstantDlg.h"


// CGammaconstantDlg 대화 상자

IMPLEMENT_DYNAMIC(CGammaconstantDlg, CDialogEx)

CGammaconstantDlg::CGammaconstantDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAMMACONSTANT, pParent)
	, m_gammaconstant(0)
{

}

CGammaconstantDlg::~CGammaconstantDlg()
{
}

void CGammaconstantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_gammaconstant);
}


BEGIN_MESSAGE_MAP(CGammaconstantDlg, CDialogEx)
END_MESSAGE_MAP()


// CGammaconstantDlg 메시지 처리기
