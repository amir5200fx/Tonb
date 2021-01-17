#pragma once
#ifndef _HydStatic_rArmCurve_Header
#define _HydStatic_rArmCurve_Header

#include <HydStatic_ArmCurve.hxx>

namespace tnbLib
{

	class HydStatic_rArmCurve
		: public HydStatic_ArmCurve
	{

		friend class HydStatic_CmptLib;

		/*Private Data*/

		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<HydStatic_ArmCurve>(*this);
			ar & theQs_;
		}

	protected:

		template<class... _Types>
		HydStatic_rArmCurve(_Types&&... _Args)
			: HydStatic_ArmCurve(_Args...)
		{}

	public:

		
		virtual Standard_Boolean IsEffective() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsPrim() const
		{
			return Standard_False;
		}

		virtual std::shared_ptr<HydStatic_rArmCurve>
			ExpandToPort() const = 0;

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::HydStatic_rArmCurve);

#endif // !_HydStatic_rArmCurve_Header
