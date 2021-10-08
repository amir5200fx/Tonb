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

		HydStatic_HydOffsetCurve
		(
			const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs
		)
			: theQs_(theQs)
		{}

		HydStatic_HydOffsetCurve
		(
			std::vector<std::pair<Standard_Real, Standard_Real>>&& theQs
		)
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

		TnbHydStatic_EXPORT Standard_Integer NbSpans() const;

		TnbHydStatic_EXPORT Standard_Integer LowerSpan() const;
		TnbHydStatic_EXPORT Standard_Integer UpperSpan() const;

		TnbHydStatic_EXPORT Standard_Integer FindSpan(const Standard_Real x) const;

		TnbHydStatic_EXPORT std::pair<Standard_Real, Standard_Real> Span(const Standard_Integer) const;
		TnbHydStatic_EXPORT std::pair<Standard_Real, Standard_Real> SpanValue(const Standard_Integer) const;

		//- return true if the parameter x is inside the span [lower, upper]
		TnbHydStatic_EXPORT Standard_Boolean IsInside(const Standard_Real x) const;

		TnbHydStatic_EXPORT Standard_Real Lower() const;
		TnbHydStatic_EXPORT Standard_Real Upper() const;

		TnbHydStatic_EXPORT Standard_Real FirstValue() const;
		TnbHydStatic_EXPORT Standard_Real LastValue() const;

		TnbHydStatic_EXPORT Standard_Real Value(const Standard_Real x) const;
		TnbHydStatic_EXPORT Standard_Real Value(const Standard_Integer span, const Standard_Real x) const;

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

		const auto& operator()() const
		{
			return Qs();
		}

		virtual void SetQs(const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs)
		{
			theQs_ = theQs;
		}

		virtual void SetQs(std::vector<std::pair<Standard_Real, Standard_Real>>&& theQs)
		{
			theQs_ = std::move(theQs);
		}

		TnbHydStatic_EXPORT void CheckSpan(const Standard_Integer) const;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::HydStatic_HydOffsetCurve);

#endif // !_HydStatic_HydOffsetCurve_Header
