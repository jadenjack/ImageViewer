#pragma once


// CRawInfoDlg 대화 상자

class CRawInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRawInfoDlg)

public:
	CRawInfoDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CRawInfoDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RAWINFODIALOG };
#endif

private:
	int nHeight;
	int nWidth;
	int nFormat;

	CEdit m_EditHeight;
	CEdit m_EditWidth;

public:
	bool isTrue;
	int GetRawHeight();
	int GetRawWidth();
	int GetRawFormat();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_radio_rawFileInfo;
	afx_msg void OnClickedRadio(UINT msg);
	afx_msg void OnBnClickedOK();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedRadioGrayformat();
};
