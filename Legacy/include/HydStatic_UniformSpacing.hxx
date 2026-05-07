#pragma once
#ifndef _HydStatic_UniformSpacing_Header
#define _HydStatic_UniformSpacing_Header

#include <HydStatic_Spacing.hxx>

namespace tnbLib
{

	class HydStatic_UniformSpacing
		: public HydStatic_Spacing
	{

		/*Private Data*/

		Standard_Integer theNbSections_;

		Standard_Real theLower_;
		Standard_Real theUpper_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<HydStatic_Spacing>(*this);
			ar & theNbSections_;
			ar & theLower_;
			ar & theUpper_;
		}

	public:

		//- default constructor

		HydStatic_UniformSpacing()
		{}


		//- constructors

		TnbHydStatic_EXPORT HydStatic_UniformSpacing
		(
			const Standard_Integer theIndex,
			const word& theName
		);

		TnbHydStatic_EXPORT HydStatic_UniformSpacing
		(
			const Standard_Integer NbSections
		);

		TnbHydStatic_EXPORT HydStatic_UniformSpacing
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const Standard_Integer NbSections
		);


		//- public functions and operators

		Standard_Integer NbSections() const override
		{
			return theNbSections_;
		}

		Standard_Real Lower() const override
		{
			return theLower_;
		}

		Standard_Real Upper() const override
		{
			return theUpper_;
		}

		TnbHydStatic_EXPORT std::vector<Standard_Real> Sections() const override;

		void SetLower(const Standard_Real x)
		{
			theLower_ = x;
		}

		void SetUpper(const Standard_Real x)
		{
			theUpper_ = x;
		}

		void SetNbSections(const Standard_Integer n)
		{
			theNbSections_ = n;
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::HydStatic_UniformSpacing);

#endif // !_HydStatic_UniformSpacing_Header
