
// A_simple_testDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

extern CString ipadress;
extern char* ipadressChar;
extern int m_nAxis;


// CA_simple_testDlg �Ի���
class CA_simple_testDlg : public CDialogEx
{
// ����
public:
	CA_simple_testDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_A_SIMPLE_TEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	

public: 
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonconnect();
	afx_msg void OnBnClickedButtondisconnect();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	

private:
	CStatic text_show_if_connected;
	CButton button_disconnect;
	CButton button_connect;
	CEdit input_ipadress;

	CEdit show_CPosition;
	CEdit show_CSpeed;


	CButton button_move;
	CButton button_stop;

	
	float input_Speed;
	float input_positive_acc;
	float input_negative_acc;
		
public:
	afx_msg void OnBnClickedButtonmove();
	afx_msg void OnBnClickedButtonstop();

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
};
