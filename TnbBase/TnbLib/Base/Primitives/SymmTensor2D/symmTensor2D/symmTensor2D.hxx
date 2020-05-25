#pragma once
#ifndef _symmTensor2D_Header
#define _symmTensor2D_Header

#include <SymmTensor2DTemplate.hxx>
#include <contiguous.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	typedef SymmTensor2D<scalar> symmTensor2D;

	//- Data associated with symmTensor2D type are contiguous
	template<>
	inline bool contiguous<symmTensor2D>() { return true; }


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_symmTensor2D_Header
