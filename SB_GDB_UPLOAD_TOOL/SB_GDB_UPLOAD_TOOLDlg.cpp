
// SB_GDB_UPLOAD_TOOLDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SB_GDB_UPLOAD_TOOL.h"
#include "SB_GDB_UPLOAD_TOOLDlg.h"
#include "afxdialogex.h"
#include "EsGDBReader.h"
#include "EsTEMySQLAPI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSB_GDB_UPLOAD_TOOLDlg �Ի���



CSB_GDB_UPLOAD_TOOLDlg::CSB_GDB_UPLOAD_TOOLDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSB_GDB_UPLOAD_TOOLDlg::IDD, pParent)
	, m_nSId(1)
	, m_strUserName("")
	, m_strPassWord("")
	, m_strGDBDir("")
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSB_GDB_UPLOAD_TOOLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_strUserName);
	DDX_Text(pDX, IDC_EDIT_PASS_WORD, m_strPassWord);
	DDX_Text(pDX, IDC_EDIT_GDB_DIR, m_strGDBDir);
	DDX_Control(pDX, IDC_COMBO_SPACE_LIST, m_comboSpaceList);
}

BEGIN_MESSAGE_MAP(CSB_GDB_UPLOAD_TOOLDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_DIR, &CSB_GDB_UPLOAD_TOOLDlg::OnOpenGDBDir)
	ON_BN_CLICKED(IDC_BUTTON_SIGN_IN, &CSB_GDB_UPLOAD_TOOLDlg::OnSignIn)
	ON_BN_CLICKED(IDC_BUTTON_UPLOAD, &CSB_GDB_UPLOAD_TOOLDlg::OnUpload)
	ON_BN_CLICKED(IDCANCEL, &CSB_GDB_UPLOAD_TOOLDlg::OnCancel)
END_MESSAGE_MAP()


// CSB_GDB_UPLOAD_TOOLDlg ��Ϣ�������

BOOL CSB_GDB_UPLOAD_TOOLDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	GetDlgItem(IDC_COMBO_SPACE_LIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_OPEN_DIR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_UPLOAD)->EnableWindow(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSB_GDB_UPLOAD_TOOLDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSB_GDB_UPLOAD_TOOLDlg::OnPaint()
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSB_GDB_UPLOAD_TOOLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSB_GDB_UPLOAD_TOOLDlg::OnOpenGDBDir()
{
	BROWSEINFO bi;                                 //BROWSEINFO�ṹ��
	TCHAR Buffer[512] = _T("");
	TCHAR FullPaths[512] = _T("");
	bi.hwndOwner = m_hWnd;                         //m_hWnd��ĳ���������
	bi.pidlRoot = NULL;
	bi.pszDisplayName = Buffer;                    //����ѡ���Ŀ¼���Ļ�����
	bi.lpszTitle = _T("��ѡ��GDB�ļ���");          //�����Ĵ��ڵ�������ʾ
	bi.ulFlags = NULL;                             //BIF_RETURNONLYFSDIRS|BIF_EDITBOX|BIF_BROWSEFORCOMPUTER ;    //ֻ����Ŀ¼��������־��MSDN
	bi.lpfn = NULL;                                //�ص���������ʱ������
	bi.lParam = 0;
	bi.iImage = 0;
	ITEMIDLIST* pidl = ::SHBrowseForFolder (&bi);  //��ʾ�������ڣ�ITEMIDLIST����Ҫ
	::SHGetPathFromIDList (pidl,FullPaths);        //��ITEMIDLIST�еõ�Ŀ¼��������·��
	if(FullPaths[0]!=NULL)
	{
		m_strGDBDir=FullPaths;
		UpdateData(FALSE);
	}
}

void CSB_GDB_UPLOAD_TOOLDlg::OnSignIn()
{
	UpdateData(TRUE);

	if(m_strUserName.IsEmpty())
	{
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel(_T("�û�������Ϊ�գ�\r\n"));
		return;
	}

	if(m_strPassWord.IsEmpty())
	{
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel(_T("���벻��Ϊ�գ�\r\n"));
		return;
	}

	string strUserName = CT2A(m_strUserName.GetString());
	string strPassWord = CT2A(m_strPassWord.GetString());
	
	if(!EsLoginToTransparentEarth(strUserName, strPassWord, m_vecPairSpaceNameAndId))
	{
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel(_T("��½ʧ�ܣ�\r\n"));
		EsReset();
		return;
	}

	if(!m_vecPairSpaceNameAndId.empty())
	{
		m_comboSpaceList.ResetContent();
		for(auto pair : m_vecPairSpaceNameAndId)
		{
			m_comboSpaceList.AddString(LPCTSTR(pair.first.c_str()));
		}
		m_comboSpaceList.SetCurSel(0);
	}
	
	GetDlgItem(IDC_COMBO_SPACE_LIST)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_OPEN_DIR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_UPLOAD)->EnableWindow(TRUE);

	((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("��½�ɹ���\r\n");
}

void CSB_GDB_UPLOAD_TOOLDlg::OnUpload()
{
	//������
	m_nSId = -1;

	//��ȡsid
	int nCurIdx = m_comboSpaceList.GetCurSel();
	CString strSpaceNameSel = "";
	m_comboSpaceList.GetLBText(nCurIdx, strSpaceNameSel);

	for(auto pair : m_vecPairSpaceNameAndId)
	{
		if(pair.first.c_str() == strSpaceNameSel)
		{
			m_nSId = pair.second;
			break;
		}	
	}

	if(m_nSId == -1)
	{
		return;
	}

	//
	if(!EsInitGDBReader())
	{
		return;
	}

	//
	if(!EsUploadCollectedEpiMechanismResult())
	{
		return;
	}	

	//
}

void CSB_GDB_UPLOAD_TOOLDlg::OnCancel()
{
	CDialogEx::OnCancel();
}

void CSB_GDB_UPLOAD_TOOLDlg::EsReset()
{
	GetDlgItem(IDC_COMBO_SPACE_LIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_OPEN_DIR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_UPLOAD)->EnableWindow(FALSE);

	m_comboSpaceList.ResetContent();
	m_strGDBDir = "";
	m_nSId = -1;

	UpdateData(FALSE);
}

bool CSB_GDB_UPLOAD_TOOLDlg::EsInitGDBReader()
{
	if(m_strGDBDir.IsEmpty())
	{
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("����ѡ��GDBĿ¼��\r\n");
		return false;
	}

	string strFilePath = CT2A(m_strGDBDir.GetString());

	EsGDBReader obReader;
	if(!obReader.EsGDBInit(strFilePath))
	{
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("GDB��ȡʧ�ܣ�����Ŀ¼�Ƿ���ȷ��\r\n");
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel(obReader.EsGetError());
		return false;
	}

	return true;
}

bool CSB_GDB_UPLOAD_TOOLDlg::EsUploadCollectedEpiMechanismResult()
{
	EsGDBReader obReader;

	((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("���ڻ�ȡ�ռ���Դ���ƽ�...\r\n");
	vector<_COLLECTEDEPIMECHANISMRESULT> vec_CollectedEpiMechanismResult;
	if(!obReader.EsGetCollectedEpiMechanismResult(vec_CollectedEpiMechanismResult))
	{
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("�ռ���Դ���ƽ��ȡʧ�ܣ�\r\n");
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel(obReader.EsGetError());
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("\r\n");
		return false;
	}
	((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("�ռ���Դ���ƽ��ȡ�ɹ���\r\n");
	((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("�����ϴ��ռ���Դ���ƽ�...\r\n");
	if(!EsAddCollectedEpiMechanismResultToNetDB(m_nSId, vec_CollectedEpiMechanismResult))
	{
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("�ռ���Դ���ƽ��ϴ�ʧ�ܣ�\r\n");
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel(obReader.EsGetError());
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("\r\n");
		return false;
	}
	((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("�ռ���Դ���ƽ��ϴ��ɹ���\r\n");

	return true;
}

bool CSB_GDB_UPLOAD_TOOLDlg::EsUploadCollectedRelocationISCatalog()
{
	EsGDBReader obReader;

	((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("���ڻ�ȡ�ռ�С���ض�λĿ¼...\r\n");
	vector<_COLLECTEDRELOCATIONISCATALOG> vec_CollectedRelocationISCatalog;
	if(!obReader.EsGetCollectedRelocationISCatalog(vec_CollectedRelocationISCatalog))
	{
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("�ռ�С���ض�λĿ¼��ȡʧ�ܣ�\r\n");
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel(obReader.EsGetError());
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("\r\n");
		return false;
	}
	((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("�ռ�С���ض�λĿ¼��ȡ�ɹ���\r\n");
	((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("�����ϴ��ռ�С���ض�λĿ¼...\r\n");
	if(!EsAddCollectedRelocationISCatalogToNetDB(m_nSId, vec_CollectedRelocationISCatalog))
	{
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("�ռ�С���ض�λĿ¼�ϴ�ʧ�ܣ�\r\n");
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel(obReader.EsGetError());
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("\r\n");
		return false;
	}
	((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("�ռ�С���ض�λĿ¼�ϴ��ɹ���\r\n");

	return true;
}