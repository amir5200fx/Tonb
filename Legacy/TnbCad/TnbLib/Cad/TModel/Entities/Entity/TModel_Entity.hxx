#pragma once
#ifndef _TModel_Entity_Header
#define _TModel_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Cad_Module.hxx>

#include <memory>

namespace tnbLib
{

	class TModel_Entity
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<TModel_Entity>
	{


		/*private Data*/


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Global_Indexed>(*this);
			ar & boost::serialization::base_object<Global_Named>(*this);
		}

	protected:

		//- default constructor

		TModel_Entity()
		{}


		//- constructors

		TModel_Entity(const Standard_Integer theIndex)
			: Global_Indexed(theIndex)
			, Global_Named("TModel_Entity")
		{}

		TModel_Entity(const Standard_Integer theIndex, const word& theName)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}

	public:


		//- public functions and operators

		virtual ~TModel_Entity()
		{}

		std::shared_ptr<const TModel_Entity> This() const
		{
			return shared_from_this();
		}
	};
}


BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::TModel_Entity);

#endif // !_TModel_Entity_Header