#pragma once
#ifndef _Aft3d_FrontInfoAdaptorTemplate_Header
#define _Aft3d_FrontInfoAdaptorTemplate_Header

#include <Standard_TypeDef.hxx>
#include <Global_Serialization.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <memory>

#include "Aft_FrontTraits.hxx"

namespace tnbLib
{

	template<class FrontTraits>
	class Aft3d_FrontInfoAdaptorTemplate
	{

	public:

		typedef typename FrontTraits::nodeType nodeType;
		typedef typename FrontTraits::edgeType edgeType;
		typedef typename FrontTraits::facetType frontType;
		typedef typename FrontTraits::facetType facetType;
		typedef typename FrontTraits::elementType elementType;

	private:

		// the existed ones [12/15/2022 Payvand]

		std::shared_ptr<facetType> thePairedFacet0_;
		std::shared_ptr<facetType> thePairedFacet1_;
		std::shared_ptr<facetType> thePairedFacet2_;

		std::shared_ptr<edgeType> thePairedEdge3_;
		std::shared_ptr<edgeType> thePairedEdge4_;
		std::shared_ptr<edgeType> thePairedEdge5_;

		// the created ones [12/15/2022 Payvand]

		std::shared_ptr<facetType> theCreatedFacet0_;
		std::shared_ptr<facetType> theCreatedFacet1_;
		std::shared_ptr<facetType> theCreatedFacet2_;

		std::shared_ptr<edgeType> theCreatedEdge3_;
		std::shared_ptr<edgeType> theCreatedEdge4_;
		std::shared_ptr<edgeType> theCreatedEdge5_;


		// Private functions and operators [12/16/2022 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			Info << "WARNING! This function is not supposed to be called!" << endl;
			NotImplemented;
		}

	public:

		// default constructor [12/15/2022 Payvand]

		Aft3d_FrontInfoAdaptorTemplate()
		{}


		// constructors [12/15/2022 Payvand]


		// public functions and operators [12/15/2022 Payvand]

		const auto& PairedFacet0() const
		{
			return thePairedFacet0_;
		}

		auto& PairedFacet0Ref()
		{
			return thePairedFacet0_;
		}

		const auto& PairedFacet1() const
		{
			return thePairedFacet1_;
		}

		auto& PairedFacet1Ref()
		{
			return thePairedFacet1_;
		}

		const auto& PairedFacet2() const
		{
			return thePairedFacet2_;
		}

		auto& PairedFacet2Ref()
		{
			return thePairedFacet2_;
		}

		const auto& PairedEdge3() const
		{
			return thePairedEdge3_;
		}

		auto& PairedEdge3Ref()
		{
			return thePairedEdge3_;
		}

		const auto& PairedEdge4() const
		{
			return thePairedEdge4_;
		}

		auto& PairedEdge4Ref()
		{
			return thePairedEdge4_;
		}

		const auto& PairedEdge5() const
		{
			return thePairedEdge5_;
		}

		auto& PairedEdge5Ref()
		{
			return thePairedEdge5_;
		}

		const auto& CreatedFacet0() const
		{
			return theCreatedFacet0_;
		}

		auto& CreatedFacet0Ref()
		{
			return theCreatedFacet0_;
		}

		const auto& CreatedFacet1() const
		{
			return theCreatedFacet1_;
		}

		auto& CreatedFacet1Ref()
		{
			return theCreatedFacet1_;
		}

		const auto& CreatedFacet2() const
		{
			return theCreatedFacet2_;
		}

		auto& CreatedFacet2Ref()
		{
			return theCreatedFacet2_;
		}

		const auto& CreatedEdge3() const
		{
			return theCreatedEdge3_;
		}

		auto& CreatedEdge3Ref()
		{
			return theCreatedEdge3_;
		}

		const auto& CreatedEdge4() const
		{
			return theCreatedEdge4_;
		}

		auto& CreatedEdge4Ref()
		{
			return theCreatedEdge4_;
		}

		const auto& CreatedEdge5() const
		{
			return theCreatedEdge5_;
		}

		auto& CreatedEdge5Ref()
		{
			return theCreatedEdge5_;
		}

		void SetPairedFacet0(const std::shared_ptr<facetType>& theFacet)
		{
			thePairedFacet0_ = theFacet;
		}

		void SetPairedFacet1(const std::shared_ptr<facetType>& theFacet)
		{
			thePairedFacet1_ = theFacet;
		}

		void SetPairedFacet2(const std::shared_ptr<facetType>& theFacet)
		{
			thePairedFacet2_ = theFacet;
		}

		void SetCreatedFacet0(const std::shared_ptr<facetType>& theFacet)
		{
			theCreatedFacet0_ = theFacet;
		}

		void SetCreatedFacet1(const std::shared_ptr<facetType>& theFacet)
		{
			theCreatedFacet1_ = theFacet;
		}

		void SetCreatedFacet2(const std::shared_ptr<facetType>& theFacet)
		{
			theCreatedFacet2_ = theFacet;
		}

		void SetPairedEdge3(const std::shared_ptr<edgeType>& theEdge)
		{
			thePairedEdge3_ = theEdge;
		}

		void SetPairedEdge4(const std::shared_ptr<edgeType>& theEdge)
		{
			thePairedEdge4_ = theEdge;
		}

		void SetPairedEdge5(const std::shared_ptr<edgeType>& theEdge)
		{
			thePairedEdge5_ = theEdge;
		}

		void SetCreatedEdge3(const std::shared_ptr<edgeType>& theEdge)
		{
			theCreatedEdge3_ = theEdge;
		}

		void SetCreatedEdge4(const std::shared_ptr<edgeType>& theEdge)
		{
			theCreatedEdge4_ = theEdge;
		}

		void SetCreatedEdge5(const std::shared_ptr<edgeType>& theEdge)
		{
			theCreatedEdge5_ = theEdge;
		}

#ifdef RESET_FRONT_INFO
		void Reset()
		{
			PairedEdge3Ref() = 0;
			PairedEdge4Ref() = 0;
			PairedEdge5Ref() = 0;

			CreatedEdge3Ref() = 0;
			CreatedEdge4Ref() = 0;
			CreatedEdge5Ref() = 0;

			PairedFacet0Ref() = 0;
			PairedFacet1Ref() = 0;
			PairedFacet2Ref() = 0;

			CreatedFacet0Ref() = 0;
			CreatedFacet1Ref() = 0;
			CreatedFacet2Ref() = 0;
		}
#endif
	};
}

#endif // !_Aft3d_FrontInfoAdaptorTemplate_Header
