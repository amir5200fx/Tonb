#pragma once
#ifndef _PtdModel_ConstPar_Header
#define _PtdModel_ConstPar_Header

#include <PtdModel_Par.hxx>
#include <PtdModel_Value.hxx>

namespace tnbLib
{

	class PtdModel_ConstPar
		: public PtdModel_Par
	{

		/*Private Data*/

		PtdModel_Value theValue_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<PtdModel_Par>(*this);
			ar & theValue_;
		}


		//- default constructor

		PtdModel_ConstPar()
		{}

	public:

		//- constructors

		PtdModel_ConstPar(const Standard_Real x)
			: theValue_(x)
		{}

		PtdModel_ConstPar(const Standard_Integer theIndex, const word& theName, const Standard_Real x)
			: PtdModel_Par(theIndex, theName)
			, theValue_(x)
		{}


		//- public functions and operators

		Standard_Real Value() const override
		{
			return theValue_.Value();
		}

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdModel_ConstPar);

#endif // !_PtdModel_ConstPar_Header
