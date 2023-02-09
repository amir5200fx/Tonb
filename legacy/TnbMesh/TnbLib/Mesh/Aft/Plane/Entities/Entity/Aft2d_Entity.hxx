#pragma once
#ifndef _Aft2d_Entity_Header
#define _Aft2d_Entity_Header

#include <Mesh_Entity.hxx>

namespace tnbLib
{

	namespace legLib
	{

		class Aft2d_Entity
			: public Mesh_Entity
		{

			/*Private Data*/


			// Private functions and operators [2/1/2023 Payvand]

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& boost::serialization::base_object<Mesh_Entity>(*this);
			}

		protected:

			// default constructor [2/1/2023 Payvand]

			Aft2d_Entity()
			{}

			// constructors [2/1/2023 Payvand]

			Aft2d_Entity(const Standard_Integer theIndex)
				: Mesh_Entity(theIndex)
			{}


		public:

			// Public functions and operators [2/1/2023 Payvand]

		};
	}
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::legLib::Aft2d_Entity);

#endif // !_Aft2d_Entity_Header
