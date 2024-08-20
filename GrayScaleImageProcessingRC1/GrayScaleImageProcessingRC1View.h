
// GrayScaleImageProcessingRC1View.h: CGrayScaleImageProcessingRC1View 클래스의 인터페이스
//

#pragma once


class CGrayScaleImageProcessingRC1View : public CView
{
protected: // serialization에서만 만들어집니다.
	CGrayScaleImageProcessingRC1View() noexcept;
	DECLARE_DYNCREATE(CGrayScaleImageProcessingRC1View)

// 특성입니다.
public:
	CGrayScaleImageProcessingRC1Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CGrayScaleImageProcessingRC1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEqualImage();
	afx_msg void OnAddImage();
	afx_msg void OnMulImage();
	afx_msg void OnDivImage();
	afx_msg void OnReverseImage();
	afx_msg void OnBwImage();
	afx_msg void OnGammaImage();
	afx_msg void OnZoomoutImage();
	afx_msg void OnZoominImage();
	afx_msg void OnRotateImage();
	afx_msg void OnRotaterImage();
	afx_msg void OnUdImage();
	afx_msg void OnRlImage();
	afx_msg void OnStretchImage();
	afx_msg void OnEndinImage();
	afx_msg void OnHistoequalImage();
	afx_msg void OnEmbossImage();
	afx_msg void OnBlurImage();
	afx_msg void OnGausImage();
	afx_msg void OnSharpImage();
	afx_msg void OnEdge1Image();
	afx_msg void OnEdge2Image();
	afx_msg void OnEdge3Image();
	afx_msg void OnRobert1Image();
	afx_msg void OnRobert2Image();
	afx_msg void OnRober3Image();
	afx_msg void OnFree1Image();
	afx_msg void OnFree2Image();
	afx_msg void OnFree3Image();
	afx_msg void OnSobel1Image();
	afx_msg void OnSobel2Image();
	afx_msg void OnSobel3Image();
	afx_msg void OnLapImage();
	afx_msg void OnLogImage();
	afx_msg void OnDogImage();
};

#ifndef _DEBUG  // GrayScaleImageProcessingRC1View.cpp의 디버그 버전
inline CGrayScaleImageProcessingRC1Doc* CGrayScaleImageProcessingRC1View::GetDocument() const
   { return reinterpret_cast<CGrayScaleImageProcessingRC1Doc*>(m_pDocument); }
#endif

