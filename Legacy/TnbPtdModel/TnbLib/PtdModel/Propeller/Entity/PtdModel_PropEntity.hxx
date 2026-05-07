#pragma once
#ifndef _PtdModel_PropEntity_Header
#define _PtdModel_PropEntity_Header

#include <PtdModel_Entity.hxx>

namespace tnbLib
{

	class PtdModel_PropEntity
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


		//- constructors

		template<class... _Types>
		PtdModel_PropEntity(_Types&&... _Args)
			: PtdModel_Entity(_Args...)
		{}

	public:

		//- public functions and operators


	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdModel_PropEntity);

#endif // !_PtdModel_PropEntity_Header
