#pragma once
#ifndef _HydStatic_ArmCurve_Header
#define _HydStatic_ArmCurve_Header

#include <HydStatic_HydCurve.hxx>
#include <HydStatic_GzQP.hxx>

#include <vector>

namespace tnbLib
{

	class HydStatic_ArmCurve
		: public HydStatic_HydCurve
	{

		/*Private Data*/

		std::vector<HydStatic_GzQP> theQs_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<HydStatic_HydCurve>(*this);
			ar & theQs_;
		}

	protected:


		template<class... _Types>
		HydStatic_ArmCurve(_Types&&... _Args)
			: HydStatic_HydCurve(_Args...)
		{}

	public:

		TnbHydStatic_EXPORT Standard_Boolean IsIntersect(const Standard_Real thePhi) const;

		TnbHydStatic_EXPORT Standard_Real MinHeel() const;

		TnbHydStatic_EXPORT Standard_Real MaxHeel() const;

		TnbHydStatic_EXPORT Standard_Real Value(const Standard_Real thePhi) const;

		auto& ChangeQs()
		{
			return theQs_;
		}

		const auto& Qs() const
		{
			return theQs_;
		}

		void SetQs
		(
			const std::vector<HydStatic_GzQP>&& theQs
		)
		{
			theQs_ = std::move(theQs);
		}

		static std::shared_ptr<HydStatic_ArmCurve>
			Clip
			(
				const std::shared_ptr<HydStatic_ArmCurve>& theCurve,
				const Standard_Real theH0,
				const Standard_Real theH1
			)
		{
			NotImplemented;
			return nullptr;
		}
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::HydStatic_ArmCurve);

#endif // !_HydStatic_ArmCurve_Header
