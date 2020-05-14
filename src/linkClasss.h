#pragma once
#ifndef _MYDLL_H_
#define _MYDLL_H_

extern "C" {
#ifdef _DLL_SAMPLE
#define DLL_SAMPLE_API __declspec(dllexport)
#else
#define DLL_SAMPLE_API __declspec(dllimport)
#endif

  DLL_SAMPLE_API bool ShapTo3Dtile(const char* filename, const char* dest, const char* height);
#undef  DLL_SAMPLE_API
}
#endif
