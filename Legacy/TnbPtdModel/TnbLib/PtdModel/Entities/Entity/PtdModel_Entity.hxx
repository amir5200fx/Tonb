#pragma once
#ifndef _PtdModel_Entity_Header
#define _PtdModel_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <PtdModel_Module.hxx>

#include <Global_Serialization.hxx>

#include <memory>

namespace tnbLib
{

	class PtdModel_Entity
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<PtdModel_Entity>
	{

		/*Private Data*/


		//- private functions and operators

		friend boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Global_Indexed>(*this);
			ar & boost::serialization::base_object<Global_Named>(*this);
		}

	protected:

		//- default constructor

		PtdModel_Entity()
		{}


		//- constructors

		PtdModel_Entity(const Standard_Integer theIndex, const word& theName)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}

	public:

		//- public functions and operators

		virtual ~PtdModel_Entity()
		{}
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdModel_Entity);

#endif // !_PtdModel_Entity_Header
