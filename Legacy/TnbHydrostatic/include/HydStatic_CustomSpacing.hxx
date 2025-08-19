#pragma once
#ifndef _HydStatic_CustomSpacing_Header
#define _HydStatic_CustomSpacing_Header

#include <HydStatic_Spacing.hxx>

#include <vector>

namespace tnbLib
{

	class HydStatic_CustomSpacing
		: public HydStatic_Spacing
	{

		/*Private Data*/


		std::vector<Standard_Real> theX_;

		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<HydStatic_Spacing>(*this);
		}

	protected:



	public:

		//- default constructor

		HydStatic_CustomSpacing()
		{}


		//- constructors

		HydStatic_CustomSpacing(const std::vector<Standard_Real>& xs)
			: theX_(xs)
		{}

		HydStatic_CustomSpacing(std::vector<Standard_Real>&& xs)
			: theX_(std::move(xs))
		{}

		TnbHydStatic_EXPORT HydStatic_CustomSpacing
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::vector<Standard_Real>& xs
		);

		TnbHydStatic_EXPORT HydStatic_CustomSpacing
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::vector<Standard_Real>&& xs
		);


		//- public functions and operators

		const auto& Xs() const
		{
			return theX_;
		}

		Standard_Integer NbSections() const override
		{
			return (Standard_Integer)theX_.size();
		}

		TnbHydStatic_EXPORT Standard_Real Lower() const override;

		TnbHydStatic_EXPORT Standard_Real Upper() const override;

		std::vector<Standard_Real> Sections() const override
		{
			return theX_;
		}


	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::HydStatic_CustomSpacing);

#endif // !_HydStatic_CustomSpacing_Header
