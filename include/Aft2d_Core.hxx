#pragma once
#ifndef _Aft2d_Core_Header
#define _Aft2d_Core_Header

#include <Aft2d_CoreTemplate.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Aft2d_OptNode_Calculator.hxx>
#include <Aft2d_CoreBase.hxx>
#include <Aft2d_CoreFwd.hxx>

namespace tnbLib
{

	typedef Aft2d_CoreTemplate<Aft2d_OptNode_Calculator, Geo2d_SizeFunction>
		Aft2d_Core;
}

#endif // !_Aft2d_Core_Header