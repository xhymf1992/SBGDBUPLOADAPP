#pragma once

#define EXPORT_SBFGDBAPI
#ifdef EXPORT_SBFGDBAPI
#define EXPORTSBFGDBAPI __declspec(dllexport)
#else
#define EXPORTSBFGDBAPI __declspec(dllimport)
#endif // EXPORT_SBFGDBAPI