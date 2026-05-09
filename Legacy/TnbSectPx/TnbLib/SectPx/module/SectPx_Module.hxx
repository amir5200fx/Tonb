#pragma once
#ifndef _SectPx_Module_Header
#define _SectPx_Module_Header

#ifdef TnbSectPx_STATIC_DEFINE
#define TnbSectPx_EXPORT
#else
#ifdef TnbSectPx_EXPORT_DEFINE
#define TnbSectPx_EXPORT __declspec(dllexport)
#else
#define TnbSectPx_EXPORT __declspec(dllimport)
#endif // TnbSectPx_EXPORT_DEFINE
#endif // TnbSectPx_STATIC_DEFINE

#endif // !_SectPx_Module_Header
