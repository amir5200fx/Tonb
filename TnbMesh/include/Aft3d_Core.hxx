#pragma once
#ifndef _Aft3d_Core_Header
#define _Aft3d_Core_Header

#include <Aft3d_CoreTemplate.hxx>
#include <Aft3d_OptNode_Calculator.hxx>
#include <Aft3d_CoreBase.hxx>
#include <Aft3d_CoreFwd.hxx>
#include <Geo3d_SizeFunction.hxx>

namespace tnbLib
{

	typedef Aft3d_CoreTemplate<Aft3d_OptNode_Calculator, Geo3d_SizeFunction>
		Aft3d_Core;
}

#endif // !_Aft3d_Core_Header
