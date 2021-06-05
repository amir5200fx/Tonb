#pragma once
#ifndef _PtdModel_BladeProfile_Header
#define _PtdModel_BladeProfile_Header

#include <Global_Done.hxx>
#include <PtdModel_PropEntity.hxx>

#include <Standard_Handle.hxx>

class Geom2d_Curve;

#include <TColgp_Array1OfPnt2d.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_PropParameters;

	class PtdModel_BladeProfile
		: public PtdModel_PropEntity
		, public Global_Done
	{

		/*Private Data*/

		Handle(Geom2d_Curve) theGeometry_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);

	public:


		//- default constructor
		PtdModel_BladeProfile()
		{}

		//- constructors

		TnbPtdModel_EXPORT PtdModel_BladeProfile
		(
			const Standard_Integer theIndex, 
			const word& theName
		);

		TnbPtdModel_EXPORT PtdModel_BladeProfile(const Handle(Geom2d_Curve)&);

		TnbPtdModel_EXPORT PtdModel_BladeProfile(Handle(Geom2d_Curve)&&);


		//- public functions and operators

		inline void SetGeometry(const Handle(Geom2d_Curve)&);
		inline void SetGeometry(Handle(Geom2d_Curve) && );

		const auto& Geometry() const
		{
			return theGeometry_;
		}

		TnbPtdModel_EXPORT std::vector<Standard_Real>
			RetrieveValues
			(
				const std::vector<Standard_Real>&
			) const;

		//virtual void CreateProfile(const std::shared_ptr<PtdModel_PropParameters>&) = 0;


		//- static functions and operators

		static TnbPtdModel_EXPORT std::shared_ptr<PtdModel_BladeProfile>
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

#include <PtdModel_BladeProfileI.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdModel_BladeProfile);

#endif // !_PtdModel_BladeProfile_Header
