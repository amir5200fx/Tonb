#pragma once
#ifndef _Marine_Load_Header
#define _Marine_Load_Header

#include <Marine_CoordinatedEntity.hxx>
#include <Marine_VesselParam_FRCE.hxx>
#include <Marine_VesselParam_LCG.hxx>
#include <Marine_VesselParam_VCG.hxx>
#include <Marine_VesselParam_TCG.hxx>
#include <Marine_LoadType.hxx>

namespace tnbLib
{

	class Marine_Load
		: public Marine_CoordinatedEntity
	{

		/*Private Data*/

		marineLib::FRCE theValue_;

		marineLib::LCG theLcg_;
		marineLib::VCG theVcg_;
		marineLib::TCG theTcg_;


		//- private functions and operators

		friend boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);
			ar & theValue_;

			ar & theLcg_;
			ar & theVcg_;
			ar & theTcg_;
		}

	protected:


		Marine_Load()
		{}


	public:

		const auto& Value() const
		{
			return theValue_;
		}

		auto& Value()
		{
			return theValue_;
		}

		const auto& Lcg() const
		{
			return theLcg_;
		}

		auto& Lcg()
		{
			return theLcg_;
		}

		const auto& Vcg() const
		{
			return theVcg_;
		}

		auto& Vcg()
		{
			return theVcg_;
		}

		const auto& Tcg() const
		{
			return theTcg_;
		}

		auto& Tcg()
		{
			return theTcg_;
		}

		virtual Marine_LoadType Type() const = 0;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Marine_Load);

#endif // !_Marine_Load_Header
