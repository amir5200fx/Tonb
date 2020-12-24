#pragma once
#ifndef _NModel_Entity_Header
#define _NModel_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Cad_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>

namespace tnbLib
{

	class NModel_Entity
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<NModel_Entity>
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Global_Indexed>(*this);
			ar & boost::serialization::base_object<Global_Named>(*this);
		}

	protected:

		//- default constructor

		NModel_Entity()
		{}


		//- constructors

		TnbCad_EXPORT NModel_Entity
		(
			const Standard_Integer theIndex
		);

		TnbCad_EXPORT NModel_Entity
		(
			const Standard_Integer theIndex,
			const word& theName
		);

	public:

		virtual ~NModel_Entity()
		{}
	};
}

#endif // !_NModel_Entity_Header
