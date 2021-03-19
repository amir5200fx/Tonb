#pragma once
#ifndef _HydStatic_rArmCurve_Header
#define _HydStatic_rArmCurve_Header

#include <HydStatic_ArmCurve.hxx>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_rAuCurve;

	class HydStatic_rArmCurve
		: public HydStatic_ArmCurve
	{

		friend class HydStatic_CmptLib;

		/*Private Data*/

		std::shared_ptr<HydStatic_rAuCurve> theAuCurve_;

		//- private functions and operators

		TNB_SERIALIZATION(TnbHydStatic_EXPORT);

	protected:

		template<class... _Types>
		HydStatic_rArmCurve(_Types&&... _Args)
			: HydStatic_ArmCurve(_Args...)
		{}

	public:


		Standard_Boolean HasAuCurve() const
		{
			return (Standard_Boolean)theAuCurve_;
		}

		const auto& AuCurve() const
		{
			return theAuCurve_;
		}
		
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

		void SetAuCurve
		(
			const std::shared_ptr<HydStatic_rAuCurve>&& theCurve
		)
		{
			theAuCurve_ = std::move(theCurve);
		}

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::HydStatic_rArmCurve);

#endif // !_HydStatic_rArmCurve_Header
