#pragma once
#ifndef _GModel_Entity_Header
#define _GModel_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Cad_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>

namespace tnbLib
{

	class GModel_Entity
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<GModel_Entity>
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

		GModel_Entity()
		{}

		//- constructors

		TnbCad_EXPORT GModel_Entity
		(
			const Standard_Integer theIndex
		);

		TnbCad_EXPORT GModel_Entity
		(
			const Standard_Integer theIndex,
			const word& theName
		);

	public:


		//- public functions and operators

		virtual ~GModel_Entity()
		{}

		std::shared_ptr<const GModel_Entity> This() const
		{
			return shared_from_this();
		}
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::GModel_Entity);

#endif // !_GModel_Entity_Header
