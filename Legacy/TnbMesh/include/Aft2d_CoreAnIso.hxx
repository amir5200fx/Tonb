#pragma once
#ifndef _Aft2d_CoreAnIso_Header
#define _Aft2d_CoreAnIso_Header

#include <Aft2d_CoreAnIsoTemplate.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Geo2d_MetricFunction.hxx>
#include <Aft2d_OptNodeAnIso_Calculator.hxx>
#include <Aft2d_CoreBaseAnIso.hxx>
#include <Aft2d_CoreAnIsoFwd.hxx>

namespace tnbLib
{

	typedef Aft2d_CoreAnIsoTemplate
		<
		Aft2d_OptNodeAnIso_Calculator,
		Geo2d_SizeFunction, Geo2d_MetricFunction
		>
		Aft2d_CoreAnIso;
}


#endif // !_Aft2d_CoreAnIso_Header