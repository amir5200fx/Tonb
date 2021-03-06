#pragma once
#ifndef _LegModel_NozzelType1_Header
#define _LegModel_NozzelType1_Header

#include <Standard_Handle.hxx>
#include <Global_Done.hxx>
#include <LegModel_CtrlNet.hxx>
#include <LegModel_NozzelType1_Parameters.hxx>
#include <LegModel_Surface.hxx>
#include <LegModel_SectionCtrlPts.hxx>

class Geom2d_Curve;

namespace tnbLib
{

	class LegModel_NozzelType1
		: public nozzle::NozzleType1_Params
		, public Global_Done
	{

		/*Private Data*/

		Handle(Geom2d_Curve) theProfile_;

		legModel::geomSurface theHull_;

		void CreateProfile();

	public:

		LegModel_NozzelType1()
		{}

		const nozzle::NozzleType1_Params& Parameters() const
		{
			return *this;
		}

		const auto& Profile() const
		{
			return theProfile_;
		}

		void Perform();
	};
}

#endif // !_LegModel_NozzelType1_Header
