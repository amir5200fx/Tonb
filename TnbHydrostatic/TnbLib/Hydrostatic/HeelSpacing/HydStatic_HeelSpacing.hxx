#pragma once
#ifndef _HydStatic_HeelSpacing_Header
#define _HydStatic_HeelSpacing_Header

#include <Global_Done.hxx>
#include <HydStatic_Entity.hxx>
#include <HydStatic_CurveMakerType.hxx>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_Spacing;

	class HydStatic_HeelSpacing
		: public HydStatic_Entity
		, public Global_Done
	{

		/* Private Data*/

		std::shared_ptr<HydStatic_Spacing> theSpacing_;


		TNB_SERIALIZATION(TnbHydStatic_EXPORT);

	protected:

		HydStatic_HeelSpacing()
		{}

		TnbHydStatic_EXPORT HydStatic_HeelSpacing
		(
			const Standard_Integer theIndex, 
			const word& theName
		);


		void SetSpacing
		(
			const std::shared_ptr<HydStatic_Spacing>& theSpacing
		)
		{
			theSpacing_ = theSpacing;
		}

		void SetSpacing
		(
			std::shared_ptr<HydStatic_Spacing>&& theSpacing
		)
		{
			theSpacing_ = std::move(theSpacing);
		}

	public:

		const auto& Spacing() const
		{
			return theSpacing_;
		}

		TnbHydStatic_EXPORT virtual Standard_Boolean IsArbitrary() const;

		TnbHydStatic_EXPORT virtual Standard_Boolean IsAsymmetric() const;

		TnbHydStatic_EXPORT virtual Standard_Boolean IsStarboard() const;

		virtual hydStcLib::CurveMakerType HeelType() const = 0;

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::HydStatic_HeelSpacing);

#endif // !_HydStatic_HeelSpacing_Header
