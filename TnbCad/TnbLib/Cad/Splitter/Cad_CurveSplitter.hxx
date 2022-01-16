#pragma once
#ifndef _Cad_CurveSplitter_Header
#define _Cad_CurveSplitter_Header

#include <Global_Done.hxx>
#include <Cad_Module.hxx>

#include <Standard_Handle.hxx>

// Forward Declarations [1/16/2022 Amir]
class Geom_Curve;

namespace tnbLib
{

	class Cad_CurveSplitter
		: public Global_Done
	{

		/*Private Data*/

		Handle(Geom_Curve) theCurve_;

	public:

		// default constructor [1/16/2022 Amir]

		Cad_CurveSplitter()
		{}


		// constructors [1/16/2022 Amir]


		// public functions and operators [1/16/2022 Amir]
	};
}

#endif // !_Cad_CurveSplitter_Header
