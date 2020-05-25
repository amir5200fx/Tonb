#pragma once
#ifndef _floatVector_Header
#define _floatVector_Header

#include <VectorTemplate.hxx>
#include <contiguous.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	typedef Vector<float> floatVector;

	//- Data associated with floatVector type are contiguous
#if !defined(WM_SP)
	template<>
	inline bool contiguous<floatVector>() { return true; }
#endif

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_floatVector_Header
