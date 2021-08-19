#pragma once
#ifndef _PtdModel_SectionCurve_Header
#define _PtdModel_SectionCurve_Header

#include <PtdModel_Entity.hxx>

#include <Standard_Handle.hxx>

class Geom2d_Curve;

#include <TColgp_Array1OfPnt2d.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>

#include <vector>

namespace tnbLib
{

	class PtdModel_SectionCurve
		: public PtdModel_Entity
	{


		/*Private Data*/

		Handle(Geom2d_Curve) theGeometry_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);

	public:

		//- default constructor
		PtdModel_SectionCurve()
		{}


		//- constructors

		TnbPtdModel_EXPORT PtdModel_SectionCurve
		(
			const Standard_Integer theIndex,
			const word& theName
		);

		TnbPtdModel_EXPORT PtdModel_SectionCurve(const Handle(Geom2d_Curve)&);

		TnbPtdModel_EXPORT PtdModel_SectionCurve(Handle(Geom2d_Curve) && );


		//- public functions and operators

		inline void SetGeometry(const Handle(Geom2d_Curve)&);
		inline void SetGeometry(Handle(Geom2d_Curve) && );

		const auto& Geometry() const
		{
			return theGeometry_;
		}

		//- static functions and operators

		static TnbPtdModel_EXPORT std::shared_ptr<PtdModel_SectionCurve>
			MakeProfile
			(
				const TColgp_Array1OfPnt2d& thePoles,
				const TColStd_Array1OfReal& theWeights,
				const TColStd_Array1OfReal& theKnots,
				const TColStd_Array1OfInteger& theMults,
				const Standard_Integer theDegree
			);
	};
}

#include <PtdModel_SectionCurveI.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdModel_SectionCurve);

#endif // !_PtdModel_SectionCurve_Header
