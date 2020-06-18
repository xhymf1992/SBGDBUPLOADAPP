#pragma once


#define EXPORT_TEMYSQLAPI
#ifdef EXPORT_TEMYSQLAPI
#define EXPORTTEMYSQLAPI  __declspec( dllexport )
#else
#define EXPORTTEMYSQLAPI   __declspec( dllimport )
#endif
