
// A_simple_testDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "A_simple_test.h"
#include "A_simple_testDlg.h"
#include "afxdialogex.h"
#include "zauxdll2.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


ZMC_HANDLE       g_handle = NULL;				//���������Ӿ��
CString ipadress;
char* ipadressChar;
int m_nAxis = 0;



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CA_simple_testDlg �Ի���



CA_simple_testDlg::CA_simple_testDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_A_SIMPLE_TEST_DIALOG, pParent)
	, input_Speed(0)
	, input_positive_acc(0)
	, input_negative_acc(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CA_simple_testDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_show_if_connected, text_show_if_connected);
	DDX_Control(pDX, IDC_BUTTON_disconnect, button_disconnect);
	DDX_Control(pDX, IDC_BUTTON_connect, button_connect);
	DDX_Control(pDX, IDC_input_IPAdress, input_ipadress);
	DDX_Control(pDX, IDC_BUTTON_connect, button_connect);
	DDX_Control(pDX, IDC_show_CPosition, show_CPosition);
	DDX_Control(pDX, IDC_show_CSpeed, show_CSpeed);

	DDX_Control(pDX, IDC_BUTTON_move, button_move);
	DDX_Control(pDX, IDC_BUTTON_stop, button_stop);
	DDX_Text(pDX, IDC_input_Speed, input_Speed);
	DDV_MinMaxFloat(pDX, input_Speed, 0, 100);
	DDX_Text(pDX, IDC_input_positive_acc, input_positive_acc);
	DDV_MinMaxFloat(pDX, input_positive_acc, 0, 20);
	DDX_Text(pDX, IDC_input_negative_acc, input_negative_acc);
	DDV_MinMaxFloat(pDX, input_negative_acc, 0, 20);
}

BEGIN_MESSAGE_MAP(CA_simple_testDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_connect, &CA_simple_testDlg::OnBnClickedButtonconnect)
	ON_BN_CLICKED(IDC_BUTTON_disconnect, &CA_simple_testDlg::OnBnClickedButtondisconnect)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_move, &CA_simple_testDlg::OnBnClickedButtonmove)
	ON_BN_CLICKED(IDC_BUTTON_stop, &CA_simple_testDlg::OnBnClickedButtonstop)
END_MESSAGE_MAP()


// CA_simple_testDlg ��Ϣ�������

BOOL CA_simple_testDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_nAxis = 0; //ѡ����1
	
	input_ipadress.SetWindowTextW(TEXT("�����������IP��ַ"));		//��ʼ�� ����IP��ַ �ı�������е��ַ���ʾ
	show_CPosition.SetWindowTextW(TEXT("��δ���λ������"));		//��ʼ�� ��ʾλ�� �ı�������е��ַ���ʾ
	show_CSpeed.SetWindowTextW(TEXT("��δ����ٶ�����"));			//��ʼ�� ��ʾ�ٶ� �ı�������е��ַ���ʾ

	input_Speed=0;				//��ʼ�� �����ٶ� �ı�������е��ַ���ʾ
	input_positive_acc=0;		//��ʼ�� ����������ٶ� �ı�������е��ַ���ʾ
	input_negative_acc=0;		//��ʼ�� ���÷�����ٶ� �ı�������е��ַ���ʾ

	UpdateData(FALSE);          //�������ڵ������ϴ����ؼ�





	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CA_simple_testDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CA_simple_testDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

void CA_simple_testDlg::OnClose() 
{ 
	if (NULL != g_handle)
	{
		KillTimer(1);						//�ض�ʱ��
		ZAux_Close(g_handle);
		g_handle = NULL;
		
	}
		CDialog::OnClose();
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CA_simple_testDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CA_simple_testDlg::OnBnClickedButtonconnect()
{
		
	if (NULL != g_handle)
	{
		ZAux_Close(g_handle);
		g_handle = NULL;
	}
	
	input_ipadress.GetWindowTextW(ipadress);  //��ȡip��ַ������е�ip��ַ��������ֱ��ʹ��

	// �����￪ʼ���� CString �� char* ��ת��������һ���궨��
	USES_CONVERSION;
	//����ת��
	ipadressChar = T2A(ipadress.GetBuffer(0));
	ipadress.ReleaseBuffer();
	//ת������
	int32 connectresult;
	connectresult=ZAux_OpenEth(ipadressChar, &g_handle);    //�������ӵ����������������ӽ��

	
	if (ERR_SUCCESS != connectresult)
	{
		g_handle = NULL;
		//��û�гɹ����ӵ����������򵯳�������ʾ���Գ�������
		MessageBox(TEXT("�볢���������ӵ�������"), TEXT("δ�ɹ�����"));
		return;
	}

	
	text_show_if_connected.SetWindowTextW(TEXT("������")); //�����ӵ�������������ʾ����״̬Ϊ������
	button_connect.EnableWindow(FALSE); //���Ӻ�������Ӱ�ť����ֹ����

	SetTimer(1, 100, NULL);//�򿪶�ʱ��

}


void CA_simple_testDlg::OnBnClickedButtondisconnect()
{
	if (NULL != g_handle)
	{
		KillTimer(1);						//�ض�ʱ��
		ZAux_Close(g_handle);
		g_handle = NULL;
		text_show_if_connected.SetWindowTextW(TEXT("�ѶϿ�")); //��ʾ����״̬Ϊ�ѶϿ�
		show_CPosition.SetWindowTextW(TEXT("��δ���λ������")); //��ʼ�� ��ʾλ�� �ı�������е��ַ���ʾ
		show_CSpeed.SetWindowTextW(TEXT("��δ����ٶ�����")); //��ʼ�� ��ʾ�ٶ� �ı�������е��ַ���ʾ
		button_connect.EnableWindow(TRUE); //�ָ����Ӱ�ť
	}
}


void CA_simple_testDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (NULL == g_handle)
	{
		MessageBox(_T("�������δ����"));                                  //��ʾ��������Ͽ�����
		return;
	}
	if (1 == nIDEvent)
	{
		
		
		CString stringPosition;
		CString stringSpeed;
		float position = 0;
		ZAux_Direct_GetDpos(g_handle, m_nAxis, &position);          //��ȡ��ǰ��λ��
		stringPosition.Format(_T("%.2f"), position);
		show_CPosition.SetWindowTextW(stringPosition);

		float NowSp = 0;
		ZAux_Direct_GetVpSpeed(g_handle, m_nAxis, &NowSp);          //��ȡ��ǰ���ٶ�
		stringSpeed.Format(_T("%.2f"), NowSp);
		show_CSpeed.SetWindowTextW(stringSpeed);
				
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CA_simple_testDlg::OnBnClickedButtonmove()
{
	if (NULL == g_handle)
	{
		MessageBox(_T("���ӶϿ�״̬"));
		return;
	}

	UpdateData(TRUE);//����Ի����ϵĲ���

	int status = 0;
	ZAux_Direct_GetIfIdle(g_handle, m_nAxis, &status);           //�жϵ�ǰ���Ƿ��Ѿ���ʼ�˶�

	if (status == 0) //�Ѿ����˶���
		return;
	
	//�趨������ 1 Ҳ�����巽��ʽ�Ĳ������ŷ�	
	ZAux_Direct_SetAtype(g_handle,m_nAxis, 1);

	//�趨����ģʽ���߼����� 0��ʾ������+����	
	ZAux_Direct_SetInvertStep(g_handle,m_nAxis, 0);

	//�������嵱��	1��ʾ��һ������Ϊ��λ ������Ϊ1MM������������������λΪMM
	ZAux_Direct_SetUnits(g_handle,m_nAxis, 1);

	//�趨�ٶȣ��Ӽ���
	ZAux_Direct_SetLspeed(g_handle,m_nAxis, 0);		//�趨��ʼ�ٶ�Ϊ��
	ZAux_Direct_SetSpeed(g_handle, m_nAxis, input_Speed);
	ZAux_Direct_SetAccel(g_handle, m_nAxis, input_positive_acc);
	ZAux_Direct_SetDecel(g_handle, m_nAxis, input_negative_acc);


	//�趨S����ʱ�� ����Ϊ0��ʾ���μӼ��٣�����0ΪS���˶����˴�Ϊ10
	ZAux_Direct_SetSramp(g_handle, m_nAxis, 10);

	//��������(�ٶ�ģʽ)
	//ZAux_Direct_Singl_Vmove(g_handle, m_nAxis, m_bLogic ? 1 : 0);
	//��m_bLogicΪtrue��Ϊ�����˶�����֮Ϊ�����˶�������Ĭ��ֻ�������˶�����
	ZAux_Direct_Singl_Vmove(g_handle, m_nAxis, true ? 1 : 0);
	
	UpdateData(FALSE);
}


void CA_simple_testDlg::OnBnClickedButtonstop()
{
	if (NULL == g_handle)
	{
		MessageBox(_T("���ӶϿ�״̬"));
		return;
	}

	ZAux_Direct_Singl_Cancel(g_handle, m_nAxis, 2);//�����ŷ�������ֹͣ
}


void CA_simple_testDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialogEx::OnOK();
}
