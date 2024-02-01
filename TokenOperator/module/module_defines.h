#pragma once
#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif
#define DTE_EXPORTS EXTERN __declspec(dllexport)
#define DTE_IMPORTS __declspec(dllimport)