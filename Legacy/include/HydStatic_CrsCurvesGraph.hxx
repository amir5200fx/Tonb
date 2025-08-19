#pragma once
#ifndef _HydStatic_CrsCurvesGraph_Header
#define _HydStatic_CrsCurvesGraph_Header

#include <Global_Done.hxx>
#include <HydStatic_Entity.hxx>
#include <HydStatic_CurveMakerType.hxx>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_CrsCurve;

	class HydStatic_CrsCurvesGraph
		: public HydStatic_Entity
		, public Global_Done
	{

	public:

		struct Heel
		{
			Standard_Real value;
		};

		struct LeverArm
		{
			Standard_Real value;
		};

	private:

		/*Private Data*/


		Standard_Real theMinDispv_;
		Standard_Real theMaxDispv_;


		TNB_SERIALIZATION(TnbHydStatic_EXPORT);

	protected:


		//- default constructor

		HydStatic_CrsCurvesGraph()
		{}


		//- constructors

		HydStatic_CrsCurvesGraph
		(
			const Standard_Integer theIndex, 
			const word& theName
		)
			: HydStatic_Entity(theIndex, theName)
		{}


		//- protected functions and operators

		TnbHydStatic_EXPORT void SetMinDispv(const Standard_Real);
		TnbHydStatic_EXPORT void SetMaxDispv(const Standard_Real);

		TnbHydStatic_EXPORT void CheckIsDone() const;

	public:

		//- public functions and operators

		virtual Standard_Integer NbCurves() const = 0;
		virtual hydStcLib::CurveMakerType CurveType() const = 0;

		TnbHydStatic_EXPORT Standard_Boolean IsInside(const Standard_Real x) const;

		TnbHydStatic_EXPORT Standard_Real MinDispv() const;
		TnbHydStatic_EXPORT Standard_Real MaxDispv() const;

		virtual std::vector<std::pair<LeverArm, Heel>> RetrieveLeverArms(const Standard_Real x) const = 0;

		TnbHydStatic_EXPORT void CheckVolume(const Standard_Real x) const;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::HydStatic_CrsCurvesGraph);

#endif // !_HydStatic_CrsCurvesGraph_Header
