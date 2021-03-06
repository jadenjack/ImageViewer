// COrderStatisticsDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Viewer.h"
#include "COrderStatisticsDlg.h"
#include "afxdialogex.h"


// COrderStatisticsDlg 대화 상자

IMPLEMENT_DYNAMIC(COrderStatisticsDlg, CDialogEx)

COrderStatisticsDlg::COrderStatisticsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OrderStatisticDIALOG, pParent)
{

}

COrderStatisticsDlg::~COrderStatisticsDlg()
{
}

afx_msg void COrderStatisticsDlg::OnOkOsfButtonClicked() {
	CString strTemp1, strTemp2;
	Edit_FilterSize1.GetWindowTextA(strTemp1);
	Edit_FilterSize2.GetWindowTextA(strTemp2);
	nFilterSize1 = atoi(strTemp1);
	nFilterSize2 = atoi(strTemp2);
	CDialog::OnOK();
}
afx_msg void COrderStatisticsDlg::OnRadioClicked(UINT msg) {
	UpdateData(TRUE);
	switch (m_radio_osf) {
	case 0:
		nOSFType = 4;
	case 1:
		nOSFType = 5;
		break;
	}
}
int COrderStatisticsDlg::GetfilterSize1() {
	return nFilterSize1;
}
int COrderStatisticsDlg::GetFilterSize2() {
	return nFilterSize2;
}
int COrderStatisticsDlg::GetOSFType() {
	return nOSFType;
}


void COrderStatisticsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_MEDIANF, m_radio_osf);
	DDX_Control(pDX, IDC_EDIT_FILTERSIZE_OSF, Edit_FilterSize1);
	DDX_Control(pDX, IDC_EDIT_MAXFILTERSIZE_OSF, Edit_FilterSize2);
}


BEGIN_MESSAGE_MAP(COrderStatisticsDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OK_OSF,&COrderStatisticsDlg::OnOkOsfButtonClicked)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_RADIO_MEDIANF,IDC_RADIO_ADAPTIVEMEDIANF,OnRadioClicked)
END_MESSAGE_MAP()


// COrderStatisticsDlg 메시지 처리기
