#pragma once
#ifndef _HydStatic_Entity_Header
#define _HydStatic_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <HydStatic_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>

namespace tnbLib
{

	class HydStatic_Entity
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<HydStatic_Entity>
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

		TnbHydStatic_EXPORT HydStatic_Entity();

		TnbHydStatic_EXPORT HydStatic_Entity
		(
			const Standard_Integer theIndex
		);

		TnbHydStatic_EXPORT HydStatic_Entity
		(
			const Standard_Integer theIndex,
			const word& theName
		);

	public:

		virtual ~HydStatic_Entity()
		{}


	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::HydStatic_Entity);

#endif // !_HydStatic_Entity_Header
