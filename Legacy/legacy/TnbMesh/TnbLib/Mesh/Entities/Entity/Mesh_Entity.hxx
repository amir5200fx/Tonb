#pragma once
#ifndef _Mesh_Entity_Header
#define _Mesh_Entity_Header

#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>
#include <Global_Indexed.hxx>

#include <memory>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	namespace legLib
	{

		class Mesh_Entity
			: public Global_Indexed
			, public std::enable_shared_from_this<Mesh_Entity>
		{

			/*Private Data*/


			// Private functions and operators [2/1/2023 Payvand]

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& boost::serialization::base_object<Global_Indexed>(*this);
			}

		protected:

			// default constructor [2/1/2023 Payvand]

			Mesh_Entity()
			{}


			// constructors [2/1/2023 Payvand]

			explicit Mesh_Entity(const Standard_Integer theIndex)
				: Global_Indexed(theIndex)
			{}

		public:

			virtual ~Mesh_Entity()
			{}

			// Public functions and operators [2/1/2023 Payvand]

			auto This() const { return this->shared_from_this(); }

		};
	}
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::legLib::Mesh_Entity);

#endif // !_Mesh_Entity_Header
