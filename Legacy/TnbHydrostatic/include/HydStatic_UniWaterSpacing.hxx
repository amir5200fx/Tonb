#pragma once
#ifndef _HydStatic_UniWaterSpacing_Header
#define _HydStatic_UniWaterSpacing_Header

#include <HydStatic_WaterSpacing.hxx>

namespace tnbLib
{

	class HydStatic_UniWaterSpacing
		: public HydStatic_WaterSpacing
	{

		/*Private Data*/

		Standard_Integer theNbSections_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<HydStatic_WaterSpacing>(*this);
			ar & theNbSections_;
		}

	public:

		//- default constructor

		HydStatic_UniWaterSpacing()
		{}


		//- constructors

		TnbHydStatic_EXPORT HydStatic_UniWaterSpacing
		(
			const Standard_Integer theIndex,
			const word& theName
		);

		TnbHydStatic_EXPORT HydStatic_UniWaterSpacing
		(
			const Standard_Integer NbSections
		);

		TnbHydStatic_EXPORT HydStatic_UniWaterSpacing
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

		TnbHydStatic_EXPORT std::vector<Standard_Real> Sections() const override;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::HydStatic_UniWaterSpacing);

#endif // !_HydStatic_UniWaterSpacing_Header
