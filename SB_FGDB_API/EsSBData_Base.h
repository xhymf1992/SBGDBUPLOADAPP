/*************************************************************************
* All rights reserved.
* 
* �ļ����ƣ�EsSBData_Base.h
* ժ    Ҫ�������GDB���ݿ�������ݽṹ
* 
* ��    �ߣ��ο�ǿ
* ������ڣ�2020/06/18
*************************************************************************/


#pragma once
#include <string>
#include <vector>

using namespace std;

struct _POINT
{
	double _x;
	double _y;
	double _z;

	_POINT():_x(0.0), _y(0.0), _z(0.0){};
	_POINT(double x, double y, double z):_x(x), _y(y), _z(z){};

};

typedef vector<_POINT> _POINTS;

struct _BASE_INFO
{
	int _OBJECTID;
	wstring _ID;
	wstring _CommentInfo;

	_BASE_INFO():_OBJECTID(-1), _ID(L""), _CommentInfo(L""){};
};