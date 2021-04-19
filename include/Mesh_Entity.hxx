#pragma once
#ifndef _Mesh_Entity_Header
#define _Mesh_Entity_Header

#include <Global_Indexed.hxx>
#include <Mesh_Module.hxx>

#include <memory>

namespace tnbLib
{

	class Mesh_Entity
		: public Global_Indexed
		, public std::enable_shared_from_this<Mesh_Entity>
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Global_Indexed>(*this);
		}

	protected:

		Mesh_Entity()
		{}

		Mesh_Entity(const Standard_Integer theIndex)
			: Global_Indexed(theIndex)
		{}

	public:

		virtual ~Mesh_Entity()
		{}
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Mesh_Entity);

#endif // !_Mesh_Entity_Header
