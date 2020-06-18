/*************************************************************************
* All rights reserved.
* 
* 文件名称：EsSBData_B8_Seismic.h
* 摘    要：地震局GDB数据库B8_Seismic表数据结构
* 
* 作    者：何俊强
* 完成日期：2020/06/18
*************************************************************************/


#pragma once
#include "EsSBData_Base.h"


struct _EPIMECHANISMRESULT
{
	_BASE_INFO _baseinfo;
	_POINT _point;

	wstring _ProjectID;
	wstring _OccurrenceDate;
	wstring _OccurrenceTime;
	wstring _LocationName;
	double _Lon;
	double _Lat;
	double _Magnitude;
	wstring _Unit;
	double _Depth;
	int _SHAzimuth;
	int _StressRegime;
	int _Plane1Strike;
	int _Plane1Dip;
	int _Plane1Slip;
	int _Plane2Strike;
	int _Plane2Dip;
	int _Plane2Slip;
	int _PAzimuth;
	int _PPlunge;
	int _TAzimuth;
	int _TPlunge;
	int _BAzimuth;
	int _BPlunge;
	wstring _Method;
	wstring _Reference;

	_EPIMECHANISMRESULT():_baseinfo(), _point(), _ProjectID(L""), _OccurrenceDate(L""), _OccurrenceTime(L""), _LocationName(L""), _Lon(0.0), _Lat(0.0), _Magnitude(0.0), _Unit(L""), _Depth(0.0), 
		_SHAzimuth(0), _StressRegime(0), _Plane1Strike(0), _Plane1Dip(0), _Plane1Slip(0), _Plane2Strike(0), _Plane2Dip(0), _Plane2Slip(0), _PAzimuth(0), _PPlunge(0), _TAzimuth(0),
		_TPlunge(0), _BAzimuth(0), _BPlunge(0), _Method(L""), _Reference(L""){};

};

struct _RELOCATIONISCATALOG
{
	_BASE_INFO _baseinfo;
	_POINT _point;

	wstring _ProjectID;
	wstring _OccurrenceDate;
	wstring _OccurrenceTime;
	wstring _LocationName;
	double _Lon;
	double _Lat;
	double _MagnitudeMl;
	wstring _MagnitudeMs;
	double _Depth;
	int _Epicenter;
	double _LastAngle;

	_RELOCATIONISCATALOG():_baseinfo(), _point(), _ProjectID(L""), _OccurrenceDate(L""), _OccurrenceTime(L""), _LocationName(L""), _Lon(0.0), _Lat(0.0), _MagnitudeMl(0.0), _MagnitudeMs(L""), _Depth(0.0), 
		_Epicenter(0), _LastAngle(0.0){};
};

