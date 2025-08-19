#pragma once
#ifndef _Cad2d_SubdivideCurve_Header
#define _Cad2d_SubdivideCurve_Header

#include <Global_Done.hxx>
#include <Cad2d_Module.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [2/6/2022 Amir]
	class Pln_Curve;
	class Cad2d_CurveLength;
	class Cad2d_IntsctEntity_Segment;

	class Cad2d_SubdivideCurve
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Pln_Curve> theParent_;
		std::shared_ptr<Cad2d_CurveLength> theLength_;

		Standard_Real theTol_;

		// outputs [2/6/2022 Amir]

		std::vector<std::shared_ptr<Pln_Curve>> theSubCurves_;


		// private functions and operators [2/9/2022 Amir]

		auto& SubCurvesRef()
		{
			return theSubCurves_;
		}

	public:

		static TnbCad2d_EXPORT const Standard_Real DEFAULT_TOLERANCE;

		// default constructor [2/6/2022 Amir]

		Cad2d_SubdivideCurve()
			: theTol_(DEFAULT_TOLERANCE)
		{}


		// constructors [2/6/2022 Amir]


		// public functions and operators [2/6/2022 Amir]

		auto NbSubCurves() const
		{
			return (Standard_Integer)theSubCurves_.size();
		}

		auto Tolerance() const
		{
			return theTol_;
		}

		const auto& Parent() const
		{
			return theParent_;
		}

		const auto& CurveLength() const
		{
			return theLength_;
		}

		const auto& SubCurves() const
		{
			return theSubCurves_;
		}

		TnbCad2d_EXPORT void Perform
		(
			const std::vector<std::shared_ptr<Cad2d_IntsctEntity_Segment>>&
		);

		void SetTolerance(const Standard_Real theTol)
		{
			theTol_ = theTol;
		}
	};
}

#endif // !_Cad2d_SubdivideCurve_Header
