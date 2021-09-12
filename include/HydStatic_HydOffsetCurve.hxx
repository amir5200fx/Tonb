#pragma once
#ifndef _HydStatic_HydOffsetCurve_Header
#define _HydStatic_HydOffsetCurve_Header

#include <HydStatic_Entity.hxx>

#include <vector>

namespace tnbLib
{

	class HydStatic_HydOffsetCurve
		: public HydStatic_Entity
	{

		/*Private Data*/

		std::vector<std::pair<Standard_Real, Standard_Real>> theQs_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbHydStatic_EXPORT);

	public:

		//- default constructor

		HydStatic_HydOffsetCurve()
		{}


		//- constructors

		HydStatic_HydOffsetCurve(const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs)
			: theQs_(theQs)
		{}

		HydStatic_HydOffsetCurve(std::vector<std::pair<Standard_Real, Standard_Real>>&& theQs)
			: theQs_(std::move(theQs))
		{}


		HydStatic_HydOffsetCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs
		)
			: HydStatic_Entity(theIndex, theName)
			, theQs_(theQs)
		{}

		HydStatic_HydOffsetCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::vector<std::pair<Standard_Real, Standard_Real>>&& theQs
		)
			: HydStatic_Entity(theIndex, theName)
			, theQs_(std::move(theQs))
		{}


		//- public functions and operators

		auto NbPoints() const
		{
			return (Standard_Integer)theQs_.size();
		}

		const auto& Qs() const
		{
			return theQs_;
		}

		auto& QsRef() const
		{
			return theQs_;
		}

		void SetQs(const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs)
		{
			theQs_ = theQs;
		}

		void SetQs(std::vector<std::pair<Standard_Real, Standard_Real>>&& theQs)
		{
			theQs_ = std::move(theQs);
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::HydStatic_HydOffsetCurve);

#endif // !_HydStatic_HydOffsetCurve_Header
