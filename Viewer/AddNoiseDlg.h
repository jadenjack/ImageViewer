#pragma once
#include "AddNoiseTab_1.h"
#include "AddNoiseTab_2.h"

// CAddNoiseDlg 대화 상자

class CAddNoiseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddNoiseDlg)
private:
	CAddNoiseTab_1 Tab1;
	CAddNoiseTab_2 Tab2;

	CWnd* m_pwndShow;

	float value_1;//GN=mena, spn = sn_prob
	float value_2;//gn = stdev, spn = pn_prob
	int NoiseType;
public:
	CAddNoiseDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAddNoiseDlg();

	float GetVal_1();
	float GetVal_2();
	int GetNoiseType();
	BOOL OnInitDialog();
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDNOISEDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_mainTab;
	afx_msg void OnTcnSelchangeAddnoisetab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
};
