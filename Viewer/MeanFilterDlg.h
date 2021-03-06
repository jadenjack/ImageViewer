#pragma once


// MeanFilterDlg 대화 상자

class MeanFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MeanFilterDlg)
private:
	int m_radio_mf;
	int nFilterSize;
	int nMeanFilterType;
	int Q;
	CEdit Edit_FilterSize;
	CEdit Edit_Q;

public:
	afx_msg void OnOkMfButtonClicked();
	afx_msg void OnRadioClicked(UINT msg);
	int GetFilterSize();
	int GetMeanFilterType();
	int GetQ();
	MeanFilterDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MeanFilterDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MeanFilterDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNoisefilteringMeanfilter();
};
