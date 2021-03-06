#pragma once


// CFilterDlg 대화 상자

class CFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFilterDlg)


public:
	CFilterDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CFilterDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FilterDIALOG };
#endif
private:
	CStatic m_EditFIltersize;
	int nFilterSize;
	int nFilterType;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedRadio(UINT msg);

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	int m_radio_Filtertype;
	int getFilterSize();
	int getFilterType();
};
