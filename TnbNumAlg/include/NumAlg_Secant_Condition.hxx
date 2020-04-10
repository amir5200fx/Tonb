#pragma once
#ifndef _NumAlg_Secant_Condition_Header
#define _NumAlg_Secant_Condition_Header

namespace tnbLib
{

	enum class NumAlg_Secant_Condition
	{
		LEVEL_EXCEEDED,
		ZERODIVIDE,
		CONVERGED
	};
}

#endif // !_NumAlg_Secant_Condition_Header
