#pragma once
#ifndef _PtdModel_RadialSection_Header
#define _PtdModel_RadialSection_Header

#include <PtdModel_Entity.hxx>
#include <PtdModel_Module.hxx>

#include <Standard_Handle.hxx>

class Geom2d_Curve;

#include <vector>

namespace tnbLib
{

	//- Forward Declarations

	class PtdModel_RadialSection
		: public PtdModel_Entity
	{

		/*Private Data*/

		Standard_Real theRadius_;

		std::vector<Handle(Geom2d_Curve)> theCurves_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);

	public:

		//- default constructor

		PtdModel_RadialSection()
		{}

		//- constructors

		PtdModel_RadialSection
		(
			const std::vector<Handle(Geom2d_Curve)>& theCurves,
			const Standard_Real theRadius
		)
			: theCurves_(theCurves)
			, theRadius_(theRadius)
		{}

		PtdModel_RadialSection
		(
			std::vector<Handle(Geom2d_Curve)>&& theCurves,
			const Standard_Real theRadius
		)
			: theCurves_(std::move(theCurves))
			, theRadius_(theRadius)
		{}

		PtdModel_RadialSection
		(
			const Standard_Integer theIndex, 
			const word& theName,
			const std::vector<Handle(Geom2d_Curve)>& theCurves,
			const Standard_Real theRadius
		)
			: PtdModel_Entity(theIndex, theName)
			, theCurves_(theCurves)
			, theRadius_(theRadius)
		{}

		PtdModel_RadialSection
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::vector<Handle(Geom2d_Curve)>&& theCurves,
			const Standard_Real theRadius
		)
			: PtdModel_Entity(theIndex, theName)
			, theCurves_(std::move(theCurves))
			, theRadius_(theRadius)
		{}


		//- public functions and operators

		const auto& Curves() const
		{
			return theCurves_;
		}

		auto Radius() const
		{
			return theRadius_;
		}

		void SetRadius(const Standard_Real theRadius)
		{
			theRadius_ = theRadius;
		}

		void SetCurves(const std::vector<Handle(Geom2d_Curve)>& theCurves)
		{
			theCurves_ = theCurves;
		}

		void SetCurves(std::vector<Handle(Geom2d_Curve)>&& theCurves)
		{
			theCurves_ = std::move(theCurves);
		}

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdModel_RadialSection);

#endif // !_PtdModel_RadialSection_Header
