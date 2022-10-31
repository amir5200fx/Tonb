#pragma once
#ifndef _Airfoil_Entity_Header
#define _Airfoil_Entity_Header

#include <Airfoil_Module.hxx>
#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

namespace tnbLib
{

	class Airfoil_Entity
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/


		// Private functions and operators [10/30/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Global_Indexed>(*this);
			ar & boost::serialization::base_object<Global_Named>(*this);
		}

	protected:

		// default constructor [10/30/2022 Amir]

		Airfoil_Entity()
		{}

		// constructors [10/30/2022 Amir]

		Airfoil_Entity(const Standard_Integer theIndex, const word& theName)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}

	public:

		// public functions and operators [10/30/2022 Amir]

		virtual ~Airfoil_Entity()
		{}

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Airfoil_Entity);

#endif // !_Airfoil_Entity_Header
