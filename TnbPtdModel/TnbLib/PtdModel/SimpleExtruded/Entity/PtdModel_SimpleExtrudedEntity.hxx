#pragma once
#ifndef _PtdModel_SimpleExtrudedEntity_Header
#define _PtdModel_SimpleExtrudedEntity_Header

#include <PtdModel_Entity.hxx>

namespace tnbLib
{

	class PtdModel_SimpleExtrudedEntity
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

		PtdModel_SimpleExtrudedEntity()
		{}


		//- constructors

		PtdModel_SimpleExtrudedEntity(const Standard_Integer theIndex, const word& theName)
			: PtdModel_Entity(theIndex, theName)
		{}


	public:


		//- public functions and operators


	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdModel_SimpleExtrudedEntity);

#endif // !_PtdModel_SimpleExtrudedEntity_Header
