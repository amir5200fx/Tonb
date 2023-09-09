#pragma once
#ifndef _Geo2d_UniformNet_Header
#define _Geo2d_UniformNet_Header

#include <Entity_Connectivity.hxx>
#include <Global_Done.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	class Geo2d_UniformNet
		: public Global_Done
	{

		/*Private Data*/

		Standard_Integer theNi_;
		Standard_Integer theNj_;

		std::vector<connectivity::quadruple> theIndices_;

	public:

		// default constructor

		Geo2d_UniformNet()
		= default;

		// constructors

		// Public functions and operators

		auto Ni() const { return theNi_; }
		auto Nj() const { return theNj_; }

		const auto& Indices() const { return theIndices_; }
		auto& IndicesRef() { return theIndices_; }

		TnbGeo_EXPORT void Perform();

		void SetNi(const Standard_Integer theN) { theNi_ = theN; }
		void SetNj(const Standard_Integer theN) { theNj_ = theN; }
		
	};
}

#endif
