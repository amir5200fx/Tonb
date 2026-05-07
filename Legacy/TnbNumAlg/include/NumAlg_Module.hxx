#pragma once
#ifndef _NumAlg_Module_Header
#define _NumAlg_Module_Header

#ifdef TnbNumAlg_STATIC_DEFINE
#define TnbNumAlg_EXPORT
#else
#ifdef TnbNumAlg_EXPORT_DEFINE
#define TnbNumAlg_EXPORT __declspec(dllexport)
#else
#define TnbNumAlg_EXPORT __declspec(dllimport)
#endif // TnbNumAlg_EXPORT_DEFINE
#endif // TnbNumAlg_STATIC_DEFINE

#endif // !_NumAlg_Module_Header
