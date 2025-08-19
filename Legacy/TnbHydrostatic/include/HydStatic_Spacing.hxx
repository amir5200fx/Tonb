#pragma once
#ifndef _HydStatic_Spacing_Header
#define _HydStatic_Spacing_Header

#include <HydStatic_Entity.hxx>

namespace tnbLib
{

	class HydStatic_Spacing
		: public HydStatic_Entity
	{

		/*Private Data*/

		

		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<HydStatic_Entity>(*this);
		}

	protected:


		template<class... _Types>
		HydStatic_Spacing(_Types&&... _Args)
			: HydStatic_Entity(_Args...)
		{}

	public:

		virtual Standard_Real Lower() const = 0;

		virtual Standard_Real Upper() const = 0;


		Standard_Real NormalizedParameter(const Standard_Real x) const
		{
			return (x - Lower()) / (Upper() - Lower());
		}

		virtual Standard_Integer NbSections() const = 0;

		virtual std::vector<Standard_Real> Sections() const = 0;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::HydStatic_Spacing);

#endif // !_HydStatic_Spacing_Header
