#pragma once
#ifndef _HydStatic_AuCurve_Header
#define _HydStatic_AuCurve_Header

#include <HydStatic_HydCurve.hxx>
#include <HydStatic_GzQ.hxx>

#include <vector>

namespace tnbLib
{

	class HydStatic_AuCurve
		: public HydStatic_HydCurve
	{

		/*Private Data*/

		std::vector<HydStatic_GzQ> theQs_;


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
		HydStatic_AuCurve(_Types&&... _Args)
			: HydStatic_HydCurve(_Args...)
		{}

	public:

		auto& ChangeQs()
		{
			return theQs_;
		}

		const auto& Qs() const
		{
			return theQs_;
		}

		void SteQs
		(
			const std::vector<HydStatic_GzQ>&& theQs
		)
		{
			theQs_ = std::move(theQs);
		}

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::HydStatic_AuCurve);

#endif // !_HydStatic_AuCurve_Header
