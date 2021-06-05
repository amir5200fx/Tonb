#pragma once
#ifndef _PtdModel_FixedPar_Header
#define _PtdModel_FixedPar_Header

#include <PtdModel_Par.hxx>
#include <PtdModel_BndValue.hxx>

namespace tnbLib
{

	class PtdModel_FixedPar
		: public PtdModel_Par
	{

		/*Private Data*/

		PtdModel_BndValue theValue_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<PtdModel_Par>(*this);
			ar & theValue_;
		}

		// default constructor

		PtdModel_FixedPar()
			: theValue_(0, 1)
		{}

	public:


		//- constructors

		inline PtdModel_FixedPar(const PtdModel_BndValue& theValue);

		inline PtdModel_FixedPar(const Standard_Integer theIndex, const word& theName, const PtdModel_BndValue& theValue);

		inline PtdModel_FixedPar(PtdModel_BndValue&& theValue);

		inline PtdModel_FixedPar(const Standard_Integer theIndex, const word& theName, PtdModel_BndValue&& theValue);


		//- public functions and operators

		const auto& BndValue() const
		{
			return theValue_;
		}

		TnbPtdModel_EXPORT Standard_Real Value() const override;
	};
}

#include <PtdModel_FixedParI.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdModel_FixedPar);

#endif // !_PtdModel_FixedPar_Header
