/*************************************************************************
* All rights reserved.
* 
* �ļ����ƣ�EsGDBReader.h
* ժ    Ҫ�������GDB���ݿ��ȡ��
* 
* ��    �ߣ��ο�ǿ
* ������ڣ�2020/06/18
*************************************************************************/


#pragma once
#include <FileGDBAPI.h>
#include "EsGlobalDef.h"
#include "EsSBData_A6_CollectedSeismic.h"
#include "EsSBData_B8_Seismic.h"

using namespace std;
using namespace FileGDBAPI;

class EXPORTSBFGDBAPI EsGDBReader
{
public:
	EsGDBReader();
	~EsGDBReader();

public:
	static bool EsGDBInit(const string& strFilePath);
	char* EsGetError(){ return m_strError; }

public:
	//A1_InvestigationRegion

	//A6_CollectedSeismic
	bool EsGetCollectedEpiMechanismResult(vector<_COLLECTEDEPIMECHANISMRESULT>& vec_CollectedEpiMechanismResult);
	bool EsGetCollectedRelocationISCatalog(vector<_COLLECTEDRELOCATIONISCATALOG>& vec_CollectedRelocationISCatalog);


	//B8_Seismic
	bool EsGetEpiMechanismResult(vector<_EPIMECHANISMRESULT>& vec_EpiMechanismResult);
	bool EsGetRelocationISCatalog(vector<_RELOCATIONISCATALOG>& vec_RelocationISCatalog);

protected:
	bool EsTableOpen(const string& strTableName, Table& obTable);
	bool EsTableSearchAll(Table& obTable, EnumRows& obRows);
	void EsSetError(const wstring& strError);

	static wstring StringToWString(const string& str);
	static string WStringToString(const wstring &wstr);
	char* ws2s(const wstring& ws);

private:

	static Geodatabase m_obGDB;
	char* m_strError;

};