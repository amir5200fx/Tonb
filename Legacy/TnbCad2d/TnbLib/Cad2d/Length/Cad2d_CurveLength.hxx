#pragma once
#ifndef _Cad2d_CurveLength_Header
#define _Cad2d_CurveLength_Header

#include <Global_Done.hxx>
#include <Cad2d_Module.hxx>

namespace tnbLib
{

	// Forward Declarations [2/6/2022 Amir]
	class Pln_Curve;

	class Cad2d_CurveLength
		: public Global_Done
	{

		/*Private Data*/

	protected:

		// default constructor [2/6/2022 Amir]

		Cad2d_CurveLength()
		{}

		// constructors [2/6/2022 Amir]


	public:

		// public functions and operators [2/6/2022 Amir]

		virtual Standard_Real CalcLength(const std::shared_ptr<Pln_Curve>&) const = 0;
		virtual Standard_Real CalcLength(const std::shared_ptr<Pln_Curve>&, const Standard_Real theLower, const Standard_Real theUpper) const = 0;
	};
}

#endif // !_Cad2d_CurveLength_Header
