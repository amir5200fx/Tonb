#pragma once
#ifndef _HydStatic_WaterSpacing_Header
#define _HydStatic_WaterSpacing_Header

#include <HydStatic_Entity.hxx>

namespace tnbLib
{

	class HydStatic_WaterSpacing
		: public HydStatic_Entity
	{

		/*Private Data*/

		Standard_Real theLower_;
		Standard_Real theUpper_;

		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<HydStatic_Entity>(*this);
			ar & theLower_;
			ar & theUpper_;
		}

	protected:


		template<class... _Types>
		HydStatic_WaterSpacing(_Types&&... _Args)
			: HydStatic_Entity(_Args...)
		{}

	public:

		auto Lower() const
		{
			return theLower_;
		}

		auto Upper() const
		{
			return theUpper_;
		}

		void SetLower(const Standard_Real x)
		{
			theLower_ = x;
		}

		void SetUpper(const Standard_Real x)
		{
			theUpper_ = x;
		}

		Standard_Real NormalizedParameter(const Standard_Real x) const
		{
			return (x - Lower()) / (Upper() - Lower());
		}

		virtual Standard_Integer NbSections() const = 0;

		virtual std::vector<Standard_Real> Sections() const = 0;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::HydStatic_WaterSpacing);

#endif // !_HydStatic_WaterSpacing_Header
