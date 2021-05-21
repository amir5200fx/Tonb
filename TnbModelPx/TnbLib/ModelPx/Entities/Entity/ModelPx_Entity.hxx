#pragma once
#ifndef _ModelPx_Entity_Header
#define _ModelPx_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <ModelPx_Type.hxx>

#include <memory>

#include <TopoDS_Shape.hxx>

namespace tnbLib
{

	class ModelPx_Entity
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<ModelPx_Entity>
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Global_Indexed>(*this);
			ar & boost::serialization::base_object<Global_Named>(*this);
		}

	protected:


		//- default constructor

		ModelPx_Entity()
		{}


		//- constructors

		ModelPx_Entity(const Standard_Integer theIndex)
			: Global_Indexed(theIndex)
		{}

		ModelPx_Entity
		(
			const Standard_Integer theIndex, 
			const word& theName
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}

	public:

		virtual ~ModelPx_Entity()
		{}


		//- public functions and operators

		virtual ModelPx_Type Type() const = 0;

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::ModelPx_Entity);

#endif // !_ModelPx_Entity_Header
