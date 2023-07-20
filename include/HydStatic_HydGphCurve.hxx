#pragma once
#ifndef _HydStatic_HydGphCurve_Header
#define _HydStatic_HydGphCurve_Header

#include <HydStatic_HydCurve.hxx>

namespace tnbLib
{

	class HydStatic_HydGphCurve
		: public HydStatic_HydCurve
	{

		/*Private Data*/

		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<HydStatic_HydCurve>(*this);
		}

	protected:

		
		template<class... _Types>
		HydStatic_HydGphCurve(_Types&&... _Args)
			: HydStatic_HydCurve(_Args...)
		{}

	public:

		TnbHydStatic_EXPORT Standard_Boolean IsIntersect(const Standard_Real theT) const;

		TnbHydStatic_EXPORT Standard_Real Draft0() const;

		TnbHydStatic_EXPORT Standard_Real Draft1() const;

		TnbHydStatic_EXPORT Standard_Real Draft(const Standard_Real theT) const;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::HydStatic_HydGphCurve);

#endif // !_HydStatic_HydGphCurve_Header
