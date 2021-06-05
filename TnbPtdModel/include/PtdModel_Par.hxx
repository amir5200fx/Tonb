#pragma once
#ifndef _PtdModel_Par_Header
#define _PtdModel_Par_Header

#include <PtdModel_Entity.hxx>

namespace tnbLib
{

	class PtdModel_Par
		: public PtdModel_Entity
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<PtdModel_Entity>(*this);
		}

	protected:

		//- default constructor

		PtdModel_Par()
		{}


		//- constructors

		PtdModel_Par(const Standard_Integer theIndex, const word& theName)
			: PtdModel_Entity(theIndex, theName)
		{}

	public:

		//- public functions and operators

		virtual Standard_Real Value() const = 0;

		auto operator()() const
		{
			return Value();
		}
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdModel_Par);

#endif // !_PtdModel_Par_Header
