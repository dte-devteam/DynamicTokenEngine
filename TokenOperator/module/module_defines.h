#pragma once
namespace tokenoperator::dte_module {
	//__cplusplus
	#define DTE_EXPORTS extern "C" __declspec(dllexport)
	#define DTE_IMPORTS __declspec(dllimport)
}