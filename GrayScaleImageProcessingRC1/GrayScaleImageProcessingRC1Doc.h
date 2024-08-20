
// GrayScaleImageProcessingRC1Doc.h: CGrayScaleImageProcessingRC1Doc 클래스의 인터페이스
//


#pragma once


class CGrayScaleImageProcessingRC1Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CGrayScaleImageProcessingRC1Doc() noexcept;
	DECLARE_DYNCREATE(CGrayScaleImageProcessingRC1Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CGrayScaleImageProcessingRC1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	unsigned char** m_inImage = NULL;
	unsigned char** m_outImage = NULL;
	int m_inH = 0;
	int m_inW = 0;
	int m_outH = 0;
	int m_outW = 0;
	unsigned char** OnMalloc2D(int h, int w, int initValue);
	void OnFree2D(unsigned char** memory, int h);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	void OnEqualImage();
	void OnAddImage();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	void OnMulImage();
	void OnDivImage();
	void OnReverseImage();
	void OnBwImage();
	void OnGammaImage();
	void OnZoomoutImage();
	void OnZoominImage();
	void OnRotateImage();
	void OnRotaterImage();
	void OnUdImage();
	void OnRlImage();
	void OnStretchImage();
	void OnEndinImage();
	void OnHistoequalImage();
	void OnEmbossImage();
	double** OnMalloc3D(int h, int w);
	void OnFree3D(double** memory, int h);
	void OnBlurImage();
	void OnGausImage();
	void OnSharpImage();
	void OnEdge1Image();
	void OnEdge2Image();
	void OnEdge3Image();
	void OnRobert1Image();
	void OnRobert2Image();
	void OnRober3Image();
	void OnFree1Image();
	void OnFree2Image();
	void OnFree3Image();
	void OnSobel1Image();
	void OnSobel2Image();
	void OnSobel3Image();
	void OnLapImage();
	void OnLogImage();
	void OnDogImage();
};
