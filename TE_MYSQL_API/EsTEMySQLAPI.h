/*************************************************************************
* All rights reserved.
* 
* �ļ����ƣ�EsTEMySQLAPI.h
* ժ    Ҫ�������͸������MySQL���ݿ�ӿ�
* 
* ��    �ߣ��ο�ǿ
* ������ڣ�2020/06/18
*************************************************************************/


#pragma once
#include <vector>

#include "EsGlobalDef.h"
#include "EsGDBReader.h"

using namespace std;


/****************login in*****************/
bool EXPORTTEMYSQLAPI EsLoginToTransparentEarth(const string& strUserName, const string& strPassWord, vector<pair<string, int>>& vecPairSpaceNameAndId);


/****************A6_CollectedSeismic*****************/

//add CollectedEpiMechanismResult
bool EXPORTTEMYSQLAPI EsAddCollectedEpiMechanismResultToNetDB(const int nSId, const vector<_COLLECTEDEPIMECHANISMRESULT>& vec_CollectedEpiMechanismResult);

//add CollectedRelocationISCatalog
bool EXPORTTEMYSQLAPI EsAddCollectedRelocationISCatalogToNetDB(const int nSId, const vector<_COLLECTEDRELOCATIONISCATALOG>& vec_CollectedRelocationISCatalog);
