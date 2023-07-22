#pragma once
#ifndef _Voyage_Entity_Header
#define _Voyage_Entity_Header

#include <Voyage_Module.hxx>
#include <Global_Named.hxx>
#include <Global_Indexed.hxx>

#include <memory>

namespace tnbLib
{

	class Voyage_Entity
		: public Global_Indexed
	{

		/*Private Data*/


		// Private functions and operators [6/17/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<Global_Indexed>(*this);
		}

	protected:

		// default constructor [6/17/2023 Payvand]

		Voyage_Entity()
		{}

		// constructors [6/17/2023 Payvand]

		Voyage_Entity(const Standard_Integer theIndex)
			: Global_Indexed(theIndex)
		{}

	public:

		// public functions and operators [6/17/2023 Payvand]

		virtual ~Voyage_Entity()
		{}

	};

}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Voyage_Entity);

#endif // !_Voyage_Entity_Header
