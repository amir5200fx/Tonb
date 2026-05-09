#pragma once
#ifndef _PtdShapeFit_Entity_Header
#define _PtdShapeFit_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Global_Serialization.hxx>

namespace tnbLib
{

	class PtdShapeFit_Entity
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/


		// Private functions and operators [2/9/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<Global_Indexed>(*this);
			ar& boost::serialization::base_object<Global_Named>(*this);
		}

	protected:

		// default constructor [2/9/2023 Payvand]

		PtdShapeFit_Entity()
		{}

		// constructors [2/9/2023 Payvand]


	public:

		// Public functions and operators [2/9/2023 Payvand]

		virtual ~PtdShapeFit_Entity()
		{}

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdShapeFit_Entity);

#endif // !_PtdShapeFit_Entity_Header
