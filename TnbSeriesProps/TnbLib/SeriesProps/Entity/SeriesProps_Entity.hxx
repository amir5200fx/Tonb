#pragma once
#ifndef _SeriesProps_Entity_Header
#define _SeriesProps_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <SeriesProps_Module.hxx>

namespace tnbLib
{

	class SeriesProps_Entity
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/


		// private functions and operators [1/11/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Global_Indexed>(*this);
			ar & boost::serialization::base_object<Global_Named>(*this);
		}

	protected:

		// default constructor [1/11/2022 Amir]

		SeriesProps_Entity()
		{}

		// constructors [1/11/2022 Amir]

		SeriesProps_Entity
		(
			const Standard_Integer theIndex, 
			const word& theName
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}

	public:

		virtual ~SeriesProps_Entity()
		{}

		// public functions and operators [1/11/2022 Amir]


	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SeriesProps_Entity);

#endif // !_SeriesProps_Entity_Header
