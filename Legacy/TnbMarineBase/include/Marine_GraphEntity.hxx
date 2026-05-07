#pragma once
#ifndef _Marine_GraphEntity_Header
#define _Marine_GraphEntity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Marine_Module.hxx>

#include <memory>

namespace tnbLib
{

	class Marine_GraphEntity
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<Marine_GraphEntity>
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Global_Indexed>(*this);
			ar & boost::serialization::base_object<Global_Named>(*this);
		}

	protected:

		//- default constructor

		Marine_GraphEntity()
		{}


		//- constructors

		TnbMarine_EXPORT Marine_GraphEntity
		(
			const Standard_Integer theIndex
		);

		TnbMarine_EXPORT Marine_GraphEntity
		(
			const Standard_Integer theIndex, 
			const word& theName
		);

	public:


		//- public functions and operators

		virtual ~Marine_GraphEntity()
		{}
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Marine_GraphEntity);


#endif // !_Marine_GraphEntity_Header
