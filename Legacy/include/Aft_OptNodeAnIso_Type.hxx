#pragma once
#ifndef _Aft_OptNodeAnIso_Type_Header
#define _Aft_OptNodeAnIso_Type_Header

namespace tnbLib
{

	enum class Aft_OptNodeAnIso_Type
	{
		automatic,
		standard,
		adaptive_nonIterative,
		uniform_metric_standard,
		uniform_metric_iterative,
		uniform_metric_nonIterative
	};
}

#endif // !_Aft_OptNodeAnIso_Type_Header
