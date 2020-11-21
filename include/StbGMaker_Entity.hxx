#pragma once
#ifndef _StbGMaker_Entity_Header
#define _StbGMaker_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Global_Serialization.hxx>
#include <StbGMaker_Module.hxx>

#include <memory>

namespace tnbLib
{

	class StbGMaker_Entity
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<StbGMaker_Entity>
	{

		/*PrivateData*/


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Global_Indexed>(*this);
			ar & boost::serialization::base_object<Global_Named>(*this);
		}

	protected:

		StbGMaker_Entity()
		{}

		StbGMaker_Entity(const Standard_Integer theIndex)
			: Global_Indexed(theIndex)
		{}

		StbGMaker_Entity(const Standard_Integer theIndex, const word& theName)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}

	public:

		virtual ~StbGMaker_Entity()
		{}


	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::StbGMaker_Entity);

#endif // !_StbGMaker_Entity_Header
