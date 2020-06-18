
// SB_GDB_UPLOAD_TOOLDlg.h : ͷ�ļ�
//

#pragma once
#include <vector>
#include <string>

using namespace std;

// CSB_GDB_UPLOAD_TOOLDlg �Ի���
class CSB_GDB_UPLOAD_TOOLDlg : public CDialogEx
{
// ����
public:
	CSB_GDB_UPLOAD_TOOLDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SB_GDB_UPLOAD_TOOL_DIALOG };

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

	//
	afx_msg void OnOpenGDBDir();
	afx_msg void OnSignIn();
	afx_msg void OnUpload();
	afx_msg void OnCancel();

	DECLARE_MESSAGE_MAP()

protected:

	void EsReset();

	//init gdbreader
	bool EsInitGDBReader();

	//A6_CollectedEpiMechanismResult
	bool EsUploadCollectedEpiMechanismResult();

	//A6_CollectedRelocationISCatalog
	bool EsUploadCollectedRelocationISCatalog();

private:
	int m_nSId;

	CString m_strUserName;
	CString m_strPassWord;
	CString m_strGDBDir;

	CComboBox m_comboSpaceList;
	vector<pair<string, int>> m_vecPairSpaceNameAndId;
};
