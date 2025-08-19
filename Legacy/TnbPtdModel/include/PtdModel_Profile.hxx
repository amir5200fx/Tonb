#pragma once
#ifndef _PtdModel_Profile_Header
#define _PtdModel_Profile_Header

#include <PtdModel_Entity.hxx>
#include <Geo_AffineTrsf_PtsToUnitSqFwd.hxx>

#include <Standard_Handle.hxx>

class Geom2d_Curve;

#include <TColgp_Array1OfPnt2d.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	

	class PtdModel_Profile
		: public PtdModel_Entity
	{

		/*Private Data*/

		Handle(Geom2d_Curve) theGeometry_;

		std::shared_ptr<GeoLib::AffineTrsf_PtsToUnitSqObj> theTrsf_;

		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);

	public:


		//- default constructor
		PtdModel_Profile()
		{}

		//- constructors

		TnbPtdModel_EXPORT PtdModel_Profile
		(
			const Standard_Integer theIndex,
			const word& theName
		);

		TnbPtdModel_EXPORT PtdModel_Profile(const Handle(Geom2d_Curve)&, const std::shared_ptr<GeoLib::AffineTrsf_PtsToUnitSqObj>& theTrsf);

		TnbPtdModel_EXPORT PtdModel_Profile(Handle(Geom2d_Curve) &&, std::shared_ptr<GeoLib::AffineTrsf_PtsToUnitSqObj>&&);


		//- public functions and operators

		inline void SetGeometry(const Handle(Geom2d_Curve)&);
		inline void SetGeometry(Handle(Geom2d_Curve) && );
		inline void SetTrsf(const std::shared_ptr<GeoLib::AffineTrsf_PtsToUnitSqObj>&);
		inline void SetTrsf(std::shared_ptr<GeoLib::AffineTrsf_PtsToUnitSqObj>&&);

		const auto& Geometry() const
		{
			return theGeometry_;
		}

		const auto& Trsf() const
		{
			return theTrsf_;
		}

		TnbPtdModel_EXPORT std::vector<Standard_Real>
			RetrieveValues
			(
				const std::vector<Standard_Real>&
			) const;


		//- static functions and operators

		static TnbPtdModel_EXPORT std::shared_ptr<PtdModel_Profile>
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

#include <PtdModel_ProfileI.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdModel_Profile);

#endif // !_PtdModel_Profile_Header
