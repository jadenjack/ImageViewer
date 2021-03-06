// FilterDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Viewer.h"
#include "FilterDlg.h"
#include "afxdialogex.h"


// CFilterDlg 대화 상자

IMPLEMENT_DYNAMIC(CFilterDlg, CDialogEx)

CFilterDlg::CFilterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FilterDIALOG, pParent)
	, m_radio_Filtertype(0)
{

}

CFilterDlg::~CFilterDlg()
{
}

void CFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_AVERAGE_FILTER_RADIO, m_radio_Filtertype);
	DDX_Control(pDX, IDC_EDIT_FILTERSIZE, m_EditFIltersize);
}



BEGIN_MESSAGE_MAP(CFilterDlg, CDialogEx)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_AVERAGE_FILTER_RADIO, IDC_GAUSSIAN_FILTER_RADIO, OnClickedRadio)
	ON_BN_CLICKED(IDC_OKBUTTON4, &CFilterDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CANCELBUTTON4, &CFilterDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CFilterDlg 메시지 처리기


void CFilterDlg::OnClickedRadio(UINT msg)
{
	UpdateData(TRUE);
	nFilterType = m_radio_Filtertype;
}
void CFilterDlg::OnBnClickedOk()
{
	CString cstrTemp;
	m_EditFIltersize.GetWindowTextA(cstrTemp);
	nFilterSize = atoi(cstrTemp);
	CDialogEx::OnOK();
}


void CFilterDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}

int CFilterDlg::getFilterSize() {
	return nFilterSize;
}
int CFilterDlg::getFilterType() {
	return nFilterType;
}