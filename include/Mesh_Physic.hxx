#pragma once
#ifndef _Mesh_Physic_Header
#define _Mesh_Physic_Header

#include <Mesh_Module.hxx>
#include <Global_Named.hxx>
#include <Global_Indexed.hxx>
#include <Global_Serialization.hxx>

namespace tnbLib
{

	class Mesh_Physic
		: public Global_Named
		, public Global_Indexed
	{

		/*Private Data*/


		// Private functions and operators [7/4/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<Global_Named>(*this);
			ar& boost::serialization::base_object<Global_Indexed>(*this);
		}

	public:

		// default constructor [7/4/2023 Payvand]

		Mesh_Physic()
		{}

		// constructors [7/4/2023 Payvand]

		Mesh_Physic(const Standard_Integer theIndex, const word& theName)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}


		// Public functions and operators [7/4/2023 Payvand]



	};

}

#endif // !_Mesh_Physic_Header
